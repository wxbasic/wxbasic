-- wrap.lua
-- convert wrappers to C++ format
-- (c) 2002 David Cuny

-- convenience
false = nil
true = 1

-- set one of these for the platforms
win = false
gtk = true
unicode = false

if win == gtk then
	print( "win/gtk flags not set correctly" )
	exit(0)
end	


-- TO DO:
-- 	code the destructors so they remove references to 
--		objects in the lookup table
--
--	method for passing back values by referece?

class = {}
enum = {}
typedefOld = {}
typedefNew = {}
include = {}

classCount = 0
enumCount = 0
includeCount = 0
typedefCount = 0
lineNum = 0
skipFlag = 0
builtin = ""
ctor = ""
a = ""
b = ""
c = ""
i = 0
j = 0
tmp = ""
theClass = ""

function instr( search, pattern )
	-- emulate BASIC's instr() function
	local at = strfind( search, pattern, 1, 1 )
	if at == nil then
		return 0
	end
	return at
end

function decodeArg()
	orig = arg

	-- default value
	if instr(arg, "=") ~= 0 then
		arg, tmp = myRemove(arg, "=")
		opt = arg
		arg = tmp
		optFlag = true
	else
		if optFlag then
			print( "Error:" .. argName .. " should be optional" )
			exit(0)
		end
		opt = ""
	end

	-- const?
	if instr(arg, "const ") ~= 0 then
		isConst = true
		arg, tmp = myRemove(arg, "const")
	else
		isConst = false
	end

	-- get theType
	arg, argType = readToken(arg)
	argType = fixType(argType)
	isWx = false
	if strlen(argType) > 2 then
		if isNative(argType) then
			isWx = true
		end
	end

	-- ref?
	if instr(arg, "&") ~= 0 then
		isRef = true
		arg, tmp = myRemove(arg, "&")
	else
		isRef = false
	end

	-- pointers
	ptrs = 0
	while instr( arg, "*" ) ~= 0 do
		ptrs = ptrs + 1
		arg, tmp = myRemove(arg, "*")
	end

	arg, argName = readToken(arg)

	-- array?
	if instr(arg, "[]") ~= 0 then
		isArray = true
		arg, tmp = myRemove(arg, "[]")
	else
		isArray = false
	end

	-- handle the arg
	if isArray then
		-- drop the value, and set it to null
        declare = "if (wTheCall->parmCount > " .. (args + opts - 1) .. ") wStackPopNumber();"
		declare = declare.."\n    "..argType.." "..argName.."[1];"
		parm = argName
	
	elseif ptrs == 1 then
		if argType == "wxString" then
            pop = "wStackPopChar()"
			declare = argType .. " " .. argName
	
		else
			declare = argType .. " *" .. argName
			if isWx then
                pop = "(" .. argType .. " *)wStackPopObjectPtr( _" .. argType .. ")"
			else
                pop = "(" .. argType .. " *)wStackPopObjectPtr( NULL )"
			end
		end
	
		parm = argName
	
	elseif ptrs == 2 then
		if isWx then
            pop = "(" .. argType .. " **)wStackPopObjectPtr( _" .. argType .. ")"
		else
            pop = "(" .. argType .. " **)wStackPopObjectPtr( NULL )"
		end
		declare = argType .. " **" .. argName
		parm = argName
	
	elseif isRef then
		if argType == "wxString" then
            pop = "wStackPopChar()"
			parm = argName
			declare = argType .. " " .. argName
			
		else
			declare = argType .. " *" .. argName
			parm = "*" .. argName
	
			if isWx then
                pop = "(" .. argType .. " *)wStackPopObjectPtr( _" .. argType .. ")"
			else
                pop = "(" .. argType .. " *)wStackPopObjectPtr( 0 )"
			end
		end
	
	else
		if argType == "wxString" then
            pop = "wStackPopChar()"
			
		elseif isEnum(argType) then
            pop = "(" .. argType .. ")(int)wStackPopNumber()"
		else
            pop = "(" .. argType .. ")wStackPopNumber()"
		end
		declare = argType .. " " .. argName
		parm = argName

	end

	if isArray == False then
		if opt == "" then
			declare = declare .. " = " .. pop .. ";"
		else
			if isRef and argType ~= "wxString" then
				opt = "&" .. opt
			end
            declare = declare .. " = (wTheCall->parmCount > " .. (args + opts) .. " ? " .. pop .. " : " .. opt .. ");"
		end
	end
	
	-- properly cast the enum
	if isEnum(argType) then
		parm = "(" .. argType .. ")" .. parm
	end
	
	if isConst then
		if argType ~= "wxString" and isArray == False then
			-- only need const if assigning constant
			if opt ~= "" then
				declare = "const " .. declare
			end
		end
	end

	-- FIX?
	popCode = "\n    // "..orig.."\n    "..declare..popCode
	if argList ~= "" then
		argList = argList .. ", " .. parm
	else
		argList = argList .. parm
	end
end


function alternateCtor( a )
 
	-- build an alternate constructor for a class
	a, b = myRemove(a, "%ctor")

	-- get function name
	a, name = myRemove(a, "(")    
    write( tmp3, "wSymbol* _"..name..";\n" )
    write( tmp4, "    _"..name.." = wWrapClass( 0, _"..theClass..", \""..strlower(name).."\" );\n" )

end


function fixType(theType)
	-- if typedef is found, replace theType with typedef
	-- if enum is found, replace theType with int
	-- SHARED typedef$(), typedefCount, enum$(), enumCount

	-- look in typedefs
	local fixed = theType
	for i = 1, typedefCount do
		if typedefOld[i] == theType then
			-- change theType
			return typedefNew[i]
		end
	end
	return fixed
end

function isEnum(name)

	-- early out test
	if strsub(name, 1, 2) ~= "wx" then		
		return false
	end

	-- true if enumerated value
	for i = 1, enumCount do	
		if name == enum[i] then
			return true			
		end
	end

	return false
	
end


function isNative( name )

	-- return true if starts with 'wx' and is not enumerated
	if strsub( name, 1, 2 ) ~= "wx" then
		return false
	end

	-- false if enumerated value
	for i = 1, enumCount do
		if name == enum[i] then
			return false			
		end
	end
	
	return true
end

function trim( string )
	
	-- trim off left side
	local at = -1
	for i = 1, strlen( string ) do
		if strsub( string, i, i ) ~= " " then
			at = i
			break
		end
	end
	
	if at == -1 then
		return ""
	end
	
	string = strsub( string, at )
	
	-- trim off right side
	for i = strlen( string ), 1, -1 do
		if strsub( string, i, i ) ~= " " then
			return strsub( string, 1, i )
		end
	end
	
	return ""
end
	

function readLine()
	local text = read( infile, "*l" )
	if text == nil then
		return nil
	end
	
	local char
	-- remove cr/lf
	while 1 do
		char = strsub( text, strlen(text), strlen(text) )
		if char == "\n" or char == "\r" then
			text = strsub( text, 1, strlen(text)-1 )
		else
			break
		end
	end
	return trim( text )
end

function readToken( arg )
	local char, r, a, at
	arg = trim( arg )
	at = strlen( arg )
	for i = 1, at do
		at = i
		char = strsub( arg, i, i )
		if (char >= "a" and char <= "z")
		or (char >= "A" and char <= "Z")
		or (char >= "0" and char <= "9")
		or char == "_"
		or char == ":" then
			-- ignore, part of token
		else
			r = strsub( arg, 1, i-1 )
			if r ~= "signed" and r ~= "unsigned" then
				at = i-1
				break
			end
		end
	end

	r = strsub( arg, 1, at )
	a = strsub( arg, at+1 )
	return a, r

end

function myRemove( source, substring )
    local at = instr( source, substring )
	if at == 0 then		
		return source, ""
	end
		
	local result = trim(strsub( source, 1, at-1 ))
    source = trim( strsub( source, at + strlen( substring ) ) )
	return source, result
end


infile = openfile( "class.i", "r" )
tmp1 = openfile( "tmp.1", "w" )
tmp2 = openfile( "tmp.2", "w" )
tmp3 = openfile( "tmp.3", "w" )
tmp4 = openfile( "tmp.4", "w" )
tmp5 = openfile( "tmp.5", "w" )
tmp6 = openfile( "tmp.6", "w" );


write( tmp1, "/*************************************************************\n")
write( tmp1, "    Name:       wrap.cpp\n")
write( tmp1, "    Purpose:    Wrap wxWindows classes and methods for wxBasic\n")
write( tmp1, "    Author:     David Cuny\n")
write( tmp1, "    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>\n")
write( tmp1, "    Licence:    LGPL\n")
write( tmp1, "*************************************************************/\n")
write( tmp1, "\n")
write( tmp1, "#ifdef __BORLANDC__\n" )
write( tmp1, "    #pragma warn -8028\n" )
write( tmp1, "    #pragma warn -8006\n" )
write( tmp1, "#endif\n" )

write( tmp4, "// wInitWrappers: link methods to classes\n" )
write( tmp4, "void wInitWrappers()\n" )
write( tmp4, "{" )

stopFlag = 0

while 1 do

	-- read a line
	theLine = readLine()
	if theLine == nil then
		break
	end

	a = theLine
	lineNum = lineNum + 1	
	print( lineNum, a )

	-- prevent code in comments from being interpreted
	if instr( a, "//" ) ~= 0 then
		-- comment
		a = ""
	end

-- win:
	if instr( a, "win:" ) ~= 0 then	
		if win then		
			a = strsub( a, 6 )
		else
			a = ""
		end
	end

-- gtk:
	if instr( a, "gtk:" ) ~= 0 then	
		if gtk then
			a = strsub( a, 6 )
		else
			a = ""
		end
	end

-- %method <alias> <method> (args)
	-- %method

	if instr( a, "%method") ~= 0 then
		if skipFlag ~= 0 then
			-- ignore
			a = ""
		else
			-- extract the parts
			a, b = myRemove(a, "%method")
			a, b = myRemove(a, " ")
			a, c = myRemove(a, "(")
			args = 0
            opts = 0
			if strlen( a ) == 1 then
                -- no args
			else
				-- count the commas to figure the arg count
                -- cound the equal signs for the optional arg count
				args = 1
                opts = 0
				for i = 1, strlen( a ) do
                    -- required arg
					if strsub( a, i, i ) == "," then
						args = args + 1
					end

                    -- change to optional arg
                    if strsub( a, i, i ) == "=" then
                        args = args - 1
                        opts = opts + 1
                    end

				end
			end
				
			a = ""
			-- add the method
            write( tmp5, "    wWrapMethod( 0, _" .. theClass .. ", " ..
                "\"" .. strlower(b) .. "\", " .. c .. ", "..args..", "..opts.." );\n" )
		end
	end

-- %skip
	-- %skip
	if instr( a, "%skip" ) ~= 0 then
		a = ""
		skipFlag = -1
	end

-- %stop
	-- %stop
	if instr( a, "%stop" ) ~= 0 then
		a = ""
		break		
	end	

-- %str - string literal
    -- not struct...
    if instr( a, "%str " ) ~= 0 then
        a, b = myRemove(a, "%str")

        if instr(a, "%alias") ~= 0 then
            a, b = myRemove(a, "%alias")
            a, alias = myRemove(a, " ")
        else
            alias = ""
        end

        write( tmp6, "\n\twLiteralAddStr( \""..a.."\", "..a.." );" )

        if alias ~= "" then
            write( tmp6, "\n\twLiteralAddStr( \""..alias.."\", "..a.." );" )
            alias = ""
        end
        a = ""
    end

-- %num - numeric literal
    if instr( a, "%num " ) ~= 0 then
        a, b = myRemove(a, "%num")

        -- %rename <new name> ...
        if instr(a, "%rename") ~= 0 then
            a, b = myRemove(a, "%rename")
            a, renamed = myRemove(a, " ")
        else
            renamed = ""
        end

        if instr(a, "%alias") ~= 0 then
            a, b = myRemove(a, "%alias")
            a, alias = myRemove(a, " ")
        else
            alias = ""
        end

        if renamed ~= "" then
            write( tmp6, "\n\twLiteralAddNum( \""..renamed.."\", "..a.." );" )
        else
            write( tmp6, "\n\twLiteralAddNum( \""..a.."\", "..a.." );" )
        end

        if alias ~= "" then
            write( tmp6, "\n\twLiteralAddNum( \""..alias.."\", "..a.." );" )
            alias = ""
        end

        a = ""
    end

-- %ptr - pointer literal
    if instr( a, "%ptr " ) ~= 0 then
        a, b = myRemove(a, "%ptr")

        if instr(a, "%alias") ~= 0 then
            a, b = myRemove(a, "%alias")
            a, alias = myRemove(a, " ")
        else
            alias = ""
        end

        -- null pointer?
        if instr( a, "wxNull" ) ~= 0 then
            -- get the name without "null"
            b = "wx"..strsub(a,7)
            write( tmp6, "\n\twLiteralAddPtr( \""..a.."\", _"..theClass..", (void *) new "..b.."("..a.."));" )
        else
            write( tmp6, "\n\twLiteralAddPtr( \""..a.."\", _"..theClass..", (void *)"..a.." );" )

            if alias ~= "" then
                write( tmp6, "\n\twLiteralAddPtr( \""..alias.."\", _"..theClass..", (void *)"..a.." );" )
                alias = ""
            end

        end
        a = ""
    end


-- %builtin - for creating direct access to methods
    if instr( a, "%builtin " ) ~= 0 then
		a, b = myRemove(a, "%builtin")
		-- there could be two in a row
		if builtin == "" then
			builtin = theClass
			theClass = "builtin"
		end
	elseif builtin ~= "" then
		theClass = builtin
		builtin = ""
	end
	

-- clear prior ctor?
	if ctor ~= "" then
		theClass = ctor
		ctor = ""
	end

-- %ctor - for alternate constructors
	if instr(a, "%ctor") ~= 0 then
		alternateCtor(a)
		a, b = myRemove(a, "%ctor")
		ctor = theClass
		c = a
		c, theClass = myRemove(c, "(")
	end

-- %rename
	-- %rename <new name> ...
	if instr(a, "%rename") ~= 0 then
		a, b = myRemove(a, "%rename")
		a, renamed = myRemove(a, " ")
	else
		renamed = ""
	end


-- %alias
	-- %alias <alias> ...
	if instr(a, "%alias") == 1 then
		a, b = myRemove(a, "%alias")
		a, alias = myRemove(a, " ")
	else
		alias = ""
	end

-- %rename - in case order is %alias %rename
	-- %rename <new name> ...
	if instr(a, "%rename") ~= 0 then
		a, b = myRemove(a, "%rename")
		a, renamed = myRemove(a, " ")
	end

-- %enum
	-- %enum <name>
	if instr(a, "%enum") ~= 0 then
		a, b = myRemove(a, "%enum ")
		enumCount = enumCount + 1
		enum[enumCount] = a
		a = ""
	end

-- %typedef
	-- %typedef <name> <name>
	if instr(a, "%typedef") ~= 0 then
		a, b = myRemove(a, "%typedef ")
		typedefCount = typedefCount + 1
		a, b = myRemove(a, " ")
		typedefOld[typedefCount] = b
		typedefNew[typedefCount] = a
		a = ""
	end

-- %struct
	-- %struct <name>
	if instr(a, "%struct") ~= 0 then
		a, b = myRemove(a, "%struct ")
		typedefCount = typedefCount + 1

		-- treat as class
		classCount = classCount + 1
		class[classCount] = a
        write( tmp3, "wSymbol* _" .. a .. ";\n" )
        write( tmp4, "    _" .. a .. " = wWrapClass( 0, 0, \"" .. strlower(a) .. "\" );\n" )

		a = ""
	end


-- %class
	if instr(a, "%class") == 1 then
		if skipFlag == -1 then
			skipFlag = -2
		else
			skipFlag = 0
			a, b = myRemove(a, "%class")

			if instr(a, "%alias") ~= 0 then
				a, b = myRemove(a, "%alias")
				a, alias = myRemove(a, " ")
			else
				alias = ""
			end

			if instr(a, ",") ~= 0 then
				-- %class <CLASS>, <SUPER>
				a, theClass = myRemove(a, ",")
				super = "_" .. a
			else
				-- %class <CLASS>
				theClass = a
				super = "0"
			end

			classCount = classCount + 1
			class[classCount] = theClass
			a = ""
					
            write( tmp3, "wSymbol* " .. "_" .. theClass .. ";\n" )
            write( tmp4, "    _"..theClass.." = wWrapClass( 0, " .. super .. ", \""
                .. strlower(theClass) .. "\" );\n" )
		   
			if alias ~= "" then				
                write( tmp3, "wSymbol* _"..alias..";\n" )
                write( tmp4, "    _"..alias.." = wWrapClass( 0, _"..theClass..", \""..strlower(alias).."\" );\n" )
				alias = ""
			end
		
			-- skip if builtin
			if theClass ~= "builtin" and ctor == "" then
		
				-- the delete routine
				delName = theClass.."_del"				
				write( tmp2, "\nvoid "..delName.."()\n{" )
                write( tmp2, "\n    delete ("..theClass.." *)(wTheCall->self->ptr);" )
				write( tmp2, "\n}\n\n" )
		  
				-- ' link delete routine
                write( tmp5, "    wWrapMethod( 0, _"..theClass..", \"del\", "..delName..", 0, 0 );\n" )

			end
		end

-- %include file
	elseif instr(a, "%include") == 1 and skipFlag == 0 then
		a, b = myRemove(a, "%include")

		-- don't include multiple times
		for i = 1, includeCount do
			if a == include[i] then
				a = ""
				break
			end
		end
		if a ~= "" then
			write( tmp1, "#include "..a.."\n" )
			includeCount = includeCount + 1
			include[includeCount] = a
		end
		a = ""

	end

-- %{
	if a == "%{" then
		-- echo until "%}"
		while true do
		
			-- don't adjust padding...
			a = readLine()
			if instr(a, "%}") ~= 0 then
				break
			else
				if skipFlag == 0 then
					write( tmp2, "\n"..a )
				end
			end
		end
		a = ""
	end
	
	if instr(a, "(") == 0 then
		-- ignore, not a method
		a = ""
	end

-- virtual
	if instr(a, "virtual") == 1 then
		a, b = myRemove(a, "virtual")
	end

-- static
	if instr(a, "static") == 1 then
		a, b = myRemove(a, "static")
	end

	if a ~= "" and skipFlag == 0 then

-----------------------------------------------------------
-- function theType
-----------------------------------------------------------		

		deref = false

		-- remove const
		if instr(a, "const") == 1 then
			a, ignore = myRemove(a, "const")
			funcConst = true
		else
			funcConst = false
		end

		-- constructor?
		if instr(a, theClass.."(") ~= 0 then
			theType = "void"

		else
			-- theType should follow...
			a, theType = myRemove(a, " ")

			-- signed/unsigned?
			if theType == "unsigned" or theType == "signed" then
				a, tmp = myRemove( a, " " )
				theType = theType .. " " .. tmp
			end

		end

		-- remove the pointer (if any)
		ptr = ""
		while instr( a, "*" ) == 1 do				
			a, b = myRemove(a, "*")
			ptr = ptr .. "*"
		end

		-- this handles the case where there was no space between the type and pointer
		-- ie:  wxFoo* ...
		at = instr(theType, "*")
		if at ~= 0 then
			ptr = strsub(theType, at, strlen(theType) )
			theType = strsub(theType, 1, at - 1)
		end
		
		if instr(theType, "&") ~= 0 then
			tmp, theType = myRemove(theType, "&")
			ptr = "*"
			deref = true
		else
			deref = false
		end
		   
		-- check for typedef
		theType = fixType(theType)		

---------------------------------------------------------
-- function name
---------------------------------------------------------


		a, func = myRemove(a, "(")		
		defList = ""
		argList = ""
		preCode = ""
		popCode = ""
		hasOptional = false

		moreArgs = true
		args = 0
		opts = 0
		optFlag = false

		-- read the args
		while moreArgs do		

---------------------------------------------------------
-- process args
---------------------------------------------------------

			-- end of line?
			if a == "" then
				-- read a new line
				a = readLine()			
			end

			if instr(a, ",") ~= 0 then				
				a, arg = myRemove(a, ",")				
				
			elseif instr(a, ")") ~= 0 then				
				a, arg = myRemove(a, ")")
				moreArgs = false				

			else
				print("Error parsing args\n")
				print(a.."\n")
				exit(0)				

			end
			-- decode the args
			if arg ~= "" then
				decodeArg()				
				if optFlag == true then
					opts = opts + 1
				else
					args = args + 1
				end
			end
			
		end

		if theType ~= "void" then

			if theType == "wxString" and ptr == "" then
				defList = defList .. "\n    wxString returns;"

			elseif isNative(theType) and ptr == "" then
				-- raw object, make it a pointer
				if funcConst then
					defList = defList .. "\n    const " .. theType .. " *returns;"
				else
					defList = defList .. "\n    " .. theType .. " *returns;"
				end

			else
				if funcConst then
					defList = defList .. "\n    const " .. theType .. " " .. ptr .. "returns;"
				else
					defList = defList .. "\n    " .. theType .. " " .. ptr .. "returns;"
				end
		   
			end

		elseif ctor ~= "" then
			defList = defList .. "\n    " .. ctor .. " *returns;"


		elseif func == theClass then
			defList = defList .. "\n    " .. theClass .. " *returns;"
			
		end


---------------------------------------------------------
-- PRINT THE PROTOTYPE
---------------------------------------------------------


		write( tmp2, "\n// "..theLine )

---------------------------------------------------------
-- PRINT THE HEADER
---------------------------------------------------------

		write( tmp2, "\nvoid " )
		if theClass == func then
			funcName = theClass.."_new"

		elseif func == "~" .. theClass then
            funcName = theClass.."_finalize"
	   
		elseif renamed ~= "" then
			funcName = theClass .. "_" .. renamed
	   
		else
			funcName = theClass .. "_" .. func
	   
		end
		
		write( tmp2, funcName.."()\n{" )
		write( tmp2, "\n    "..defList )

		-- args to pop from list?
		if strlen(popCode) ~= 0 then
			write( tmp2, "\n    "..popCode )
		end

		-- any pre code?
		if strlen(preCode) ~= 0 then
			write( tmp2, "\n    "..preCode )
		end
		
		-- the actual function call
		write( tmp2, "\n    // call "..func )

		if ctor ~= "" then
			-- call alternate constructor
			write( tmp2, "\n    returns = new "..ctor.."("..argList..");" )

		elseif theClass == func then
			write( tmp2, "\n    returns = new "..theClass.."(" .. argList .. ");" )
			
		else
			if theClass == "builtin" then
				-- not really a class
				head = func

			else
				-- reference class
                head = "((" .. theClass .. " *)(wTheCall->self->ptr))->" .. func
			end

			if theType == "void" then
				write( tmp2, "\n    "..head.."("..argList..");" )

			elseif theType == "wxString" and ptr == "" then
				write( tmp2, "\n    returns = "..head.."("..argList..");" )

			elseif isNative(theType) and ptr == "" then
				-- make it a pointer
				write( tmp2, "\n    // make a pointer via copy constructor" )
				write( tmp2, "\n    returns = new "..theType.."("..head.."("..argList.."));" )

			elseif deref then
				-- make it a pointer
				write( tmp2, "\n    returns = &"..head.."("..argList..");" )

			else
				write( tmp2, "\n    returns = "..head.."("..argList..");" )
				
			end
		end
				
		-- and post code?
        write( tmp2, "\n    wWrapDerefArgs();" )

		-- return value of routine
		if theType == "void" then
			if func == theClass then
                -- constructor
                write( tmp2, "\n    wWrapSetThis( _"..theClass..", (void *)returns );" )

            elseif funcName == theClass.."_finalize" then
				-- don't put anything on the stack
                write( tmp2, "\n    // finalize doesn't leave value on stack" )
			else
				write( tmp2, "\n    // result is ignored" )
                write( tmp2, "\n    wStackPushNumber( (wNumber)0 );" )
			end

        elseif theType == "time_t" then
            write( tmp2, "\n    wStackPushDateTime( returns );" )

		elseif theType == "wxString" and ptr == "" then
            write( tmp2, "\n    wStackPushChar( (char *)(returns.c_str()), W_TRUE );" )

		elseif theType == "wxString" and ptr == "*" then
            write( tmp2, "\n    wStackPushChar( (char *)(returns->c_str()), W_TRUE );" )

		elseif isNative(theType) then
			-- wrap pointer
            write( tmp2, "\n    wWrapPushObject( _"..theType..", W_TRUE, (void *)returns );" )

			
		else
			if ptr ~= "" then
				-- generic pointer of some sort
                -- FIXME!
                -- write( tmp2, "\n    wPushPtrHandle( (wNumber)(int)returns);" )
                write( tmp2, "\n    wWrapPushObject( _"..theClass..", W_TRUE, (void *)returns );" )
			else
				-- plain number
                write( tmp2, "\n    wStackPushNumber( (wNumber)returns);" )
			end
		end

		write( tmp2, "\n}\n\n" )

		-- remove class from name
		shortName = funcName
		shortName, ignore = myRemove(shortName, "_")

		-- link
		if theClass == "builtin" then
            write( tmp5, "    wBuiltinNew( " )
		else
            write( tmp5, "    wWrapMethod( 0, _" .. theClass .. ", " )
		end
				
        write( tmp5, "\"" .. strlower(shortName) .. "\", " )
        write( tmp5, funcName .. ", " .. args .. ", " .. (args + opts) .. " );\n" )

		-- alias?
		if alias ~= "" then
			if theClass == "builtin" then
                write( tmp5, "    wBuiltinNew( " )
			else
                write( tmp5, "    wWrapMethod( 0, _" .. theClass .. ", " )
			end
			
			-- FIX?
            write( tmp5, "\""..strlower(alias).."\", "..funcName..", "..args..", " .. (args + opts) .. " );\n" )
		end

	end

end

write( tmp1, "\n\n" )
write( tmp6, "\n}" )

closefile( infile )
closefile( tmp1 )
closefile( tmp2 )
closefile( tmp3 )
closefile( tmp4 )
closefile( tmp5 )
closefile( tmp6 )

function appendFile( dest, name )
	local handle = openfile( name, "r" )
	local text
	while 1 do
		text = read( handle, "*l" )
		if text == nil then
			break
		end
		write( dest, text.."\n" )
	end
	closefile( handle )
end

-- append the files together
local handle = openfile( "wrap.cpp", "w" )
appendFile( handle, "tmp.1")	-- include files
appendFile( handle, "tmp.3" )	-- class constants
appendFile( handle, "tmp.2" )	-- wrappers
appendFile( handle, "tmp.4" )   -- initialize classes
appendFile( handle, "tmp.5" )   -- initialize class methods
appendFile( handle, "tmp.6" )   -- initialize constants

closefile( handle )

-- remove the temp files
remove( "tmp.1" )
remove( "tmp.2" )
remove( "tmp.3" )
remove( "tmp.4" )
remove( "tmp.5" )
remove( "tmp.6" )
