// these are static, and not really class members
%builtin %rename wxDateTime_ConvertYearToBC static int ConvertYearToBC(int year)
%builtin %rename wxDateTime_GetAmPmStrings static void GetAmPmStrings(wxString *am, wxString *pm)
%builtin %rename wxDateTime_GetBeginDST static wxDateTime GetBeginDST(int year = Inv_Year, Country country = Country_Default)
%builtin %rename wxDateTime_GetCountry static Country GetCountry()
%builtin %rename wxDateTime_GetCurrentYear static int GetCurrentYear(Calendar cal = Gregorian)
%builtin %rename wxDateTime_GetCurrentMonth static Month GetCurrentMonth(Calendar cal = Gregorian)
%builtin %rename wxDateTime_GetCentury static int GetCentury(int year = Inv_Year)
%builtin %rename wxDateTime_GetEndDST static wxDateTime GetEndDST(int year = Inv_Year, Country country = Country_Default)
%builtin %rename wxDateTime_GetMonthName static wxString GetMonthName(Month month, NameFlags flags = Name_Full)
%builtin %rename wxDateTime_GetNumberOfDaysInYear static wxDateTime_t GetNumberOfDays(int year, Calendar cal = Gregorian)
%builtin %rename wxDateTime_GetNumberOfDaysInMonth static wxDateTime_t GetNumberOfDays(Month month, int year = Inv_Year, Calendar cal = Gregorian)
%builtin %rename wxDateTime_GetWeekDayName static wxString GetWeekDayName(WeekDay weekday, NameFlags flags = Name_Full)
%builtin %rename wxDateTime_IsLeapYear static bool IsLeapYear(int year = Inv_Year, Calendar cal = Gregorian)
%builtin %rename wxDateTime_IsWestEuropeanCountry static bool IsWestEuropeanCountry(Country country = Country_Default)
%builtin %rename wxDateTime_IsDSTApplicable static bool IsDSTApplicable(int year = Inv_Year, Country country = Country_Default)
%builtin %rename wxDateTime_wxDateTime static wxDateTime Now()
%builtin %rename wxDateTime_SetCountry static void SetCountry(Country country)
%builtin %rename wxDateTime_Today static wxDateTime Today()
%builtin %rename wxDateTime_UNow static wxDateTime UNow()

wxDateTime()
%ctor wxDateTimeFromTimeT wxDateTime& wxDateTime(time_t timet)
%ctor wxDateTimeFromJDN wxDateTime& wxDateTime(double jdn)
%ctor wxDateTimeFromHMS wxDateTime& wxDateTime(wxDateTime_t hour, wxDateTime_t minute = 0, wxDateTime_t second = 0, wxDateTime_t millisec = 0)
%ctor wxDateTimeFromDMYwxDateTime& wxDateTime(wxDateTime_t day, Month month = Inv_Month, int Inv_Year, wxDateTime_t hour = 0, wxDateTime_t minute = 0, wxDateTime_t second = 0, wxDateTime_t millisec = 0)
wxDateTime& SetToCurrent()
wxDateTime& Set(time_t timet)
%rename SetJDN wxDateTime& Set(double jdn)
%rename SetHMS wxDateTime& Set(wxDateTime_t hour, wxDateTime_t minute = 0, wxDateTime_t second = 0, wxDateTime_t millisec = 0)
wxDateTime& Set(wxDateTime_t day, Month month = Inv_Month, int year = Inv_Year, wxDateTime_t hour = 0, wxDateTime_t minute = 0, wxDateTime_t second = 0, wxDateTime_t millisec = 0)
wxDateTime& ResetTime()
wxDateTime& SetYear(int year)
wxDateTime& SetMonth(Month month)
wxDateTime& SetDay(wxDateTime_t day)
wxDateTime& SetHour(wxDateTime_t hour)
wxDateTime& SetMinute(wxDateTime_t minute)
wxDateTime& SetSecond(wxDateTime_t second)
wxDateTime& SetMillisecond(wxDateTime_t millisecond)
bool IsValid() const
// Tm GetTm(const TimeZone& tz = Local) const
time_t GetTicks() const
int GetYear(const TimeZone& tz = Local) const
Month GetMonth(const TimeZone& tz = Local) const
wxDateTime_t GetDay(const TimeZone& tz = Local) const
WeekDay GetWeekDay(const TimeZone& tz = Local) const
wxDateTime_t GetHour(const TimeZone& tz = Local) const
wxDateTime_t GetMinute(const TimeZone& tz = Local) const
wxDateTime_t GetSecond(const TimeZone& tz = Local) const
wxDateTime_t GetMillisecond(const TimeZone& tz = Local) const
wxDateTime_t GetDayOfYear(const TimeZone& tz = Local) const
wxDateTime_t GetWeekOfYear(WeekFlags flags = Monday_First, const TimeZone& tz = Local) const
wxDateTime_t GetWeekOfMonth(WeekFlags flags = Monday_First, const TimeZone& tz = Local) const
bool IsWorkDay(Country country = Country_Default) const
bool IsGregorianDate(GregorianAdoption country = Gr_Standard) const
wxDateTime& Set(unsigned long ddt)
unsigned long GetAsDOS() const
bool IsEqualTo(const wxDateTime& datetime) const
bool IsEarlierThan(const wxDateTime& datetime) const
bool IsLaterThan(const wxDateTime& datetime) const
bool IsStrictlyBetween(const wxDateTime& t1, const wxDateTime& t2) const
bool IsBetween(const wxDateTime& t1, const wxDateTime& t2) const
bool IsSameDate(const wxDateTime& dt) const
bool IsSameTime(const wxDateTime& dt) const
bool IsEqualUpTo(const wxDateTime& dt, const wxTimeSpan& ts) const
%rename AddTS wxDateTime Add(const wxTimeSpan& diff) const
%rename SubtractTS wxDateTime Subtract(const wxTimeSpan& diff) const
%rename AddDS wxDateTime Add(const wxDateSpan& diff) const
%rename SubtractDS wxDateTime Subtract(const wxDateSpan& diff) const
wxTimeSpan Subtract(const wxDateTime& dt) const
const wxChar * ParseRfc822Date(const wxChar* date)
const wxChar * ParseFormat(const wxChar *date, const wxChar *format = "%c", const wxDateTime& dateDef = wxDefaultDateTime)
const wxChar * ParseDateTime(const wxChar *datetime)
const wxChar * ParseDate(const wxChar *date)
const wxChar * ParseTime(const wxChar *time)
wxString  Format(const wxChar *format = "%c", const TimeZone& tz = Local) const
wxString  FormatDate() const
wxString  FormatTime() const
wxString  FormatISODate() const
wxString  FormatISOTime() const
wxDateTime& SetToWeekDayInSameWeek(WeekDay weekday, WeekFlagsflags = Monday_First)
wxDateTime GetWeekDayInSameWeek(WeekDay weekday, WeekFlagsflags = Monday_First) const
wxDateTime& SetToNextWeekDay(WeekDay weekday)
wxDateTime GetNextWeekDay(WeekDay weekday) const
wxDateTime& SetToPrevWeekDay(WeekDay weekday)
wxDateTime GetPrevWeekDay(WeekDay weekday) const
bool SetToWeekDay(WeekDay weekday, int n = 1, Month month = Inv_Month, int year = Inv_Year)
wxDateTime GetWeekDay(WeekDay weekday, int n = 1, Month month = Inv_Month, int year = Inv_Year) const
bool SetToLastWeekDay(WeekDay weekday, Month month = Inv_Month, int year = Inv_Year)
wxDateTime GetLastWeekDay(WeekDay weekday, Month month = Inv_Month, int year = Inv_Year)
bool SetToTheWeek(wxDateTime_t numWeek, WeekDay weekday = Mon, WeekFlagsflags = Monday_First)
wxDateTime GetWeek(wxDateTime_t numWeek, WeekDay weekday = Mon, WeekFlagsflags = Monday_First) const
wxDateTime& SetToLastMonthDay(Month month = Inv_Month, int year = Inv_Year)
wxDateTime GetLastMonthDay(Month month = Inv_Month, int year = Inv_Year) const
wxDateTime& SetToYearDay(wxDateTime_t yday)
wxDateTime GetYearDay(wxDateTime_t yday) const
double GetJulianDayNumber() const
double GetJDN() const
double GetModifiedJulianDayNumber() const
double GetMJD() const
double GetRataDie() const
wxDateTime ToTimezone(const TimeZone& tz, bool noDST = FALSE) const
wxDateTime& MakeTimezone(const TimeZone& tz, bool noDST = FALSE)
wxDateTime ToGMT(bool noDST = FALSE) const
wxDateTime& MakeGMT(bool noDST = FALSE)
int IsDST(Country country = Country_Default) const


%num %rename wxTZ_Local TZ::Local
%num %rename wxTZ_GTM_0 TZ::GMT_0
%num %rename wxTZ_GTM_1 TZ::GMT_1
%num %rename wxTZ_GTM_2 TZ::GMT_2
%num %rename wxTZ_GTM_3 TZ::GMT_3
%num %rename wxTZ_GTM_4 TZ::GMT_4
%num %rename wxTZ_GTM_5 TZ::GMT_5
%num %rename wxTZ_GTM_6 TZ::GMT_6
%num %rename wxTZ_GTM_7 TZ::GMT_7
%num %rename wxTZ_GTM_8 TZ::GMT_8
%num %rename wxTZ_GTM_9 TZ::GMT_9
%num %rename wxTZ_GTM_10 TZ::GMT_10
%num %rename wxTZ_GTM_11 TZ::GMT_11
%num %rename wxTZ_GTM_12 TZ::GMT_12
%num %rename wxTZ_GTM0 TZ::GMT0
%num %rename wxTZ_GTM1 TZ::GMT1
%num %rename wxTZ_GTM2 TZ::GMT2
%num %rename wxTZ_GTM3 TZ::GMT3
%num %rename wxTZ_GTM4 TZ::GMT4
%num %rename wxTZ_GTM5 TZ::GMT5
%num %rename wxTZ_GTM6 TZ::GMT6
%num %rename wxTZ_GTM7 TZ::GMT7
%num %rename wxTZ_GTM8 TZ::GMT8
%num %rename wxTZ_GTM9 TZ::GMT9
%num %rename wxTZ_GTM10 TZ::GMT10
%num %rename wxTZ_GTM11 TZ::GMT11
%num %rename wxTZ_GTM12 TZ::GMT12

%num %rename wxTZ_WET TZ::WET
%num %rename wxTZ_WESTT TZ::WEST
%num %rename wxTZ_CET TZ::CET
%num %rename wxTZ_CEST TZ::CEST
%num %rename wxTZ_EET TZ::EET
%num %rename wxTZ_EEET TZ::EEET
%num %rename wxTZ_MSK TZ::MSK
%num %rename wxTZ_MSD TZ::MSD

%num %rename wxTZ_AST TZ::AST
%num %rename wxTZ_ADT TZ::ADT
%num %rename wxTZ_EST TZ::EST
%num %rename wxTZ_EDT TZ::EDT
%num %rename wxTZ_CST TZ::CST
%num %rename wxTZ_CDT TZ::CDT
%num %rename wxTZ_MST TZ::MST
%num %rename wxTZ_MDTT TZ::MDT
%num %rename wxTZ_PST TZ::PST
%num %rename wxTZ_PDT TZ::PDT
%num %rename wxTZ_HST TZ::HST
%num %rename wxTZ_SKST TZ::AKST
%num %rename wxTZ_AKDT TZ::AKST
%num %rename wxTZ_A_WST TZ::A_WST
%num %rename wxTZ_A_CST TZ::A_CST
%num %rename wxTZ_A_EST TZ::A_EST
%num %rename wxTZ_A_EEST TZ::A_EEST
%num %rename wxTZ_A_UTC TZ::A_UTC

%num %rename wxMonth_Jan wxDateTime::Month::Jan
%num %rename wxMonth_Feb wxDateTime::Month::Feb
%num %rename wxMonth_Mar wxDateTime::Month::Mar
%num %rename wxMonth_Apr wxDateTime::Month::Apr
%num %rename wxMonth_May wxDateTime::Month::May
%num %rename wxMonth_Jun wxDateTime::Month::Jun
%num %rename wxMonth_Jul wxDateTime::Month::Jul
%num %rename wxMonth_Aug wxDateTime::Month::Aug
%num %rename wxMonth_Sep wxDateTime::Month::Sep
%num %rename wxMonth_Oct wxDateTime::Month::Oct
%num %rename wxMonth_Nov wxDateTime::Month::Nov
%num %rename wxMonth_Dec wxDateTime::Month::Dec
%num %rename wxMonth_Inv_Month wxDateTime::Month::Inv_Month

%num %rename wxWeekDay_Sun wxDateTime::WeekDay::Sun
%num %rename wxWeekDay_Mon wxDateTime::WeekDay::Mon
%num %rename wxWeekDay_Tue wxDateTime::WeekDay::Tue
%num %rename wxWeekDay_Wed wxDateTime::WeekDay::Wed
%num %rename wxWeekDay_Thu wxDateTime::WeekDay::Thu
%num %rename wxWeekDay_Fri wxDateTime::WeekDay::Fri
%num %rename wxWeekDay_Sat wxDateTime::WeekDay::Sat
%num %rename wxWeekDay_Inv_WeekDay wxDateTime::WeekDay::Inv_WeekDay

%num Inv_Year

%num %rename wxNameFlags_Name_Full NameFlags::Name_Full
%num %rename wxNameFlags_Name_Abbr NameFlags::Name_Abbr
	
%num %rename Calendar_Gregorian Calendar::Gregorian
%num %rename Calendar_Julian Calendar::Julian

%num %rename wxCountry_Unknown Country::Country_Unknown
%num %rename wxCountry_Default Country::Country_Default
%num %rename wxCountry_WesternEurope_Start Country::Country_WesternEurope_Start
%num %rename wxCountry_EEC Country::Country_EEC
%num %rename wxCountry_France Country::France
%num %rename wxCountry_Germany Country::Germany
%num %rename wxCountry_UK Country::UK
%num %rename wxCountry_Russia Country::Russia
%num %rename wxCountry_USA Country::USA
	
	
%num %rename wxDefault_First WeekFlags::Default_First
%num %rename wxMonday_First WeekFlags::Monday_First
%num %rename wxSunday_First WeekFlags::Monday_First