// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Resource.h"
#include "Encoding.h"
#include "Utility.h"
#include "Base64.h"
#include "Log.h"
#include "Platform.h"

//-----------------------------------------------------------------------------
// "Builtin.Codepages"
static const std::string kCodepageASCII =
"U+0000-U+007F";

static const std::string kCodepage437 = // OEM 437
"U+0000, U+263A, U+263B, U+2665, U+2666, U+2663, U+2660, U+2022,"
"U+25D8, U+25CB, U+25D9, U+2642, U+2640, U+266A, U+266B, U+263C,"
"U+25BA, U+25C4, U+2195, U+203C, U+00B6, U+00A7, U+25AC, U+21A8,"
"U+2191, U+2193, U+2192, U+2190, U+221F, U+2194, U+25B2, U+25BC,"
"U+0020-U+007F,"
"U+00C7, U+00FC, U+00E9, U+00E2, U+00E4, U+00E0, U+00E5, U+00E7,"
"U+00EA, U+00EB, U+00E8, U+00EF, U+00EE, U+00EC, U+00C4, U+00C5,"
"U+00C9, U+00E6, U+00C6, U+00F4, U+00F6, U+00F2, U+00FB, U+00F9,"
"U+00FF, U+00D6, U+00DC, U+00A2, U+00A3, U+00A5, U+20A7, U+0192,"
"U+00E1, U+00ED, U+00F3, U+00FA, U+00F1, U+00D1, U+00AA, U+00BA,"
"U+00BF, U+2310, U+00AC, U+00BD, U+00BC, U+00A1, U+00AB, U+00BB,"
"U+2591, U+2592, U+2593, U+2502, U+2524, U+2561, U+2562, U+2556,"
"U+2555, U+2563, U+2551, U+2557, U+255D, U+255C, U+255B, U+2510,"
"U+2514, U+2534, U+252C, U+251C, U+2500, U+253C, U+255E, U+255F,"
"U+255A, U+2554, U+2569, U+2566, U+2560, U+2550, U+256C, U+2567,"
"U+2568, U+2564, U+2565, U+2559, U+2558, U+2552, U+2553, U+256B,"
"U+256A, U+2518, U+250C, U+2588, U+2584, U+258C, U+2590, U+2580,"
"U+03B1, U+00DF, U+0393, U+03C0, U+03A3, U+03C3, U+00B5, U+03C4,"
"U+03A6, U+0398, U+03A9, U+03B4, U+221E, U+03C6, U+03B5, U+2229,"
"U+2261, U+00B1, U+2265, U+2264, U+2320, U+2321, U+00F7, U+2248,"
"U+00B0, U+2219, U+00B7, U+221A, U+207F, U+00B2, U+25A0, U+00A0";

static const std::string kCodepage866 = // DOS Cyrilic
"U+0000-U+007F,"
"U+0410, U+0411, U+0412, U+0413, U+0414, U+0415, U+0416, U+0417,"
"U+0418, U+0419, U+041a, U+041b, U+041c, U+041d, U+041e, U+041f,"
"U+0420, U+0421, U+0422, U+0423, U+0424, U+0425, U+0426, U+0427,"
"U+0428, U+0429, U+042a, U+042b, U+042c, U+042d, U+042e, U+042f,"
"U+0430, U+0431, U+0432, U+0433, U+0434, U+0435, U+0436, U+0437,"
"U+0438, U+0439, U+043a, U+043b, U+043c, U+043d, U+043e, U+043f,"
"U+2591, U+2592, U+2593, U+2502, U+2524, U+2561, U+2562, U+2556,"
"U+2555, U+2563, U+2551, U+2557, U+255d, U+255c, U+255b, U+2510,"
"U+2514, U+2534, U+252c, U+251c, U+2500, U+253c, U+255e, U+255f,"
"U+255a, U+2554, U+2569, U+2566, U+2560, U+2550, U+256c, U+2567,"
"U+2568, U+2564, U+2565, U+2559, U+2558, U+2552, U+2553, U+256b,"
"U+256a, U+2518, U+250c, U+2588, U+2584, U+258c, U+2590, U+2580,"
"U+0440, U+0441, U+0442, U+0443, U+0444, U+0445, U+0446, U+0447,"
"U+0448, U+0449, U+044a, U+044b, U+044c, U+044d, U+044e, U+044f,"
"U+0401, U+0451, U+0404, U+0454, U+0407, U+0457, U+040e, U+045e,"
"U+00b0, U+2219, U+00b7, U+221a, U+2116, U+00a4, U+25a0, U+00a0";

static const std::string kCodepage1250 = // Windows Central European
"U+0000-U+007F,"
"U+20AC, U+FFFE, U+201A, U+FFFE, U+201E, U+2026, U+2020, U+2021,"
"U+FFFE, U+2030, U+0160, U+2039, U+015A, U+0164, U+017D, U+0179,"
"U+FFFE, U+2018, U+2019, U+201C, U+201D, U+2022, U+2013, U+2014,"
"U+FFFE, U+2122, U+0161, U+203A, U+015B, U+0165, U+017E, U+017A,"
"U+00A0, U+02C7, U+02D8, U+0141, U+00A4, U+0104, U+00A6, U+00A7,"
"U+00A8, U+00A9, U+015E, U+00AB, U+00AC, U+00AD, U+00AE, U+017B,"
"U+00B0, U+00B1, U+02DB, U+0142, U+00B4, U+00B5, U+00B6, U+00B7,"
"U+00B8, U+0105, U+015F, U+00BB, U+013D, U+02DD, U+013E, U+017C,"
"U+0154, U+00C1, U+00C2, U+0102, U+00C4, U+0139, U+0106, U+00C7,"
"U+010C, U+00C9, U+0118, U+00CB, U+011A, U+00CD, U+00CE, U+010E,"
"U+0110, U+0143, U+0147, U+00D3, U+00D4, U+0150, U+00D6, U+00D7,"
"U+0158, U+016E, U+00DA, U+0170, U+00DC, U+00DD, U+0162, U+00DF,"
"U+0155, U+00E1, U+00E2, U+0103, U+00E4, U+013A, U+0107, U+00E7,"
"U+010D, U+00E9, U+0119, U+00EB, U+011B, U+00ED, U+00EE, U+010F,"
"U+0111, U+0144, U+0148, U+00F3, U+00F4, U+0151, U+00F6, U+00F7,"
"U+0159, U+016F, U+00FA, U+0171, U+00FC, U+00FD, U+0163, U+02D9";

static const std::string kCodepage1251 = // Windows Cyrillic
"U+0000-U+007F,"
"U+0402, U+0403, U+201A, U+0453, U+201E, U+2026, U+2020, U+2021,"
"U+20AC, U+2030, U+0409, U+2039, U+040A, U+040C, U+040B, U+040F,"
"U+0452, U+2018, U+2019, U+201C, U+201D, U+2022, U+2013, U+2014,"
"U+003F, U+2122, U+0459, U+203A, U+045A, U+045C, U+045B, U+045F,"
"U+00A0, U+040E, U+045E, U+0408, U+00A4, U+0490, U+00A6, U+00A7,"
"U+0401, U+00A9, U+0404, U+00AB, U+00AC, U+00AD, U+00AE, U+0407,"
"U+00B0, U+00B1, U+0406, U+0456, U+0491, U+00B5, U+00B6, U+00B7,"
"U+0451, U+2116, U+0454, U+00BB, U+0458, U+0405, U+0455, U+0457,"
"U+0410, U+0411, U+0412, U+0413, U+0414, U+0415, U+0416, U+0417,"
"U+0418, U+0419, U+041A, U+041B, U+041C, U+041D, U+041E, U+041F,"
"U+0420, U+0421, U+0422, U+0423, U+0424, U+0425, U+0426, U+0427,"
"U+0428, U+0429, U+042A, U+042B, U+042C, U+042D, U+042E, U+042F,"
"U+0430, U+0431, U+0432, U+0433, U+0434, U+0435, U+0436, U+0437,"
"U+0438, U+0439, U+043A, U+043B, U+043C, U+043D, U+043E, U+043F,"
"U+0440, U+0441, U+0442, U+0443, U+0444, U+0445, U+0446, U+0447,"
"U+0448, U+0449, U+044A, U+044B, U+044C, U+044D, U+044E, U+044F";

static const std::string kCodepageTCOD =
// First row
"U+0020-U+003F,"
// Second row
"U+0040, U+005B-U+0060, U+007B-U+007E, U+2591-U+2593,"
"U+2502, U+2500, U+253C, U+2524, U+2534, U+251C, U+252C, U+2514, U+250C, U+2510, U+2518,"
"U+2598, U+259D, U+2580, U+2597, U+259A, U+2590, U+2596,"
// Third row
"U+2191, U+2193, U+2190, U+2192, U+25B2, U+25BC, U+25C4, U+25BA, U+2195, U+2194,"
"U+2610, U+2611, U+26AA, U+26AB,"
"U+2551, U+2550, U+256C, U+2563, U+2569, U+2560, U+2565, U+255A, U+2554, U+2557, U+255D,"
"U+0020, U+0002-U+0007,"
// Fourth row
"U+0041-U+005A, U+0008-U+000D,"
// Fifth row
"U+0061-U+007A";


// "Builtin.DefaultFont"
static const std::string kDefaultFont =
"iVBORw0KGgoAAAANSUhEUgAAAQAAAAFACAMAAABk9FI4AAAABGdBTUEAALGPC/xhBQAAAwBQTFRFAAAA////AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAZ3bsYwAAAQB0Uk5T////////////////////////////////////"
"////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////"
"////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////"
"////////////////////////////////////////////////AFP3ByUAAAAJcEhZcwAADsIAAA7CARUoSoAAAAAadEVYdFNvZnR3YXJlAFBhaW50Lk5FVCB2My41LjEx"
"R/NCNwAAHI5JREFUeF7tXYl2HDmOnP7/j+4h4gBA5lmXW5YUL4FABEBmFl1Vkt2zb//37w/H7wGIz/DPPyq+I+4fwD/f8xz6AfiFqhpJLAsKGmztIuV9YAn3T5m6ODJk"
"NroWJe+gN7LmfDsAbRDJhWuWcaWtyT2+j1jhiBzUvTSKBuZqjR3MtpTmjw8gZDgw2XZPVnUmzgH7h8AAxkfBu9HsESnrQBbZniIyqDEo4SnE9gASQ8Eol9UytunnwDK3"
"BQZG2ixwUQPdywdQu/ps1HaSVtUAgbffAYkh6fT5zVQ3UPFGeFVBiVV7YWT5bqf0QBRezloN0uLPOPaQ7xxAn5etGqg6J3LyFOzH9Lyg1kXl2OrMPgHfeIZMtF0W9QOY"
"wQU1OgLSkSjBauQszqB2bJplZRADWDyJ5qncwWpP+vodkCHDOlFisgt+fENablArXXd/08+iaxuD3UmDTKRCceMjMPZhQ0ZIOYTFZDbkgwjUaeb+tEJmAZuNlC7cLV3G"
"xDUaqBrV8Ueg0PZpGxXs7ncHdhuH0+/DnVs8dABH4MDh2B94qbu4dd87B/Ct8XsA4h+Ln3gA03fDDzyA8bOsncD/oOk4pwR3GZW5+gzrgL3syYtkHqFS6870KPYi0up5"
"HgVHiKbTGwfAmu400CKIaeEe1dnriUfqfCd6XiPSxtOshb2BVibqAKK4Co0mzz130oNhN47XEaboNAhWaw+uilYC2UsBVFXAAeDPnsUcgT29Mms76cGwG5omO+GfBVOA"
"Re8puAlT+pPRuVeFOIC8FPGE8/rZN6NNjdoOq9UdXLciKzi4aqri6mdwE6agLDrtFQ39ALhDj8CeFk/z1UkPht3QNmMheeo7upWkXg9tgpxzpuSdouH8I7BGoPPcq6yA"
"QVfczGBHoOvu9dwj0qSn3IusyinoS3AgioMIYlq4R89r2I/U2RHoukfPqPDHRcNeGpl7kVU5Bf8e0DcLNSDu0jNA0/Aok6tHw6YZDZVA0yrUSlo1KkdlDVICKpuT+FK/"
"Ce494PP4Cw/gvSew3ezrH8BboU9CYtahAj/xb4MTfg8AbwaJn4h4B7zrAHKfv+lE8RGYHnjv6WcvvjtUDlSdFQqrefoJPL9cK1cKjt8h8GTb7wDNTZi8ZWBvPlD+0cRN"
"PL3cCyceydd6ANAkrOjsBnXk9EXZdsEeDdv0QCzs50AQo7R5G5FWz/NUG0a0ufkdwMZ5MO34bqhY/ZF9+FehB4xVXGhaYnc/z66qmLh1AHueFm58Zxcjycju7gNvY6Rc"
"VUX1M7xZ5PRVptgrArFsGMtHYEz0oO1g343ybamhQtOWkW8eABZFwVJG7yu4GVP6cw7sVVHjBnUA0Vxj9dMQzT01VIwkI7twQl2FgVpG7yu8WeT0mRrvFAG8/qsDWCMH"
"RXNPDRWrP/JbDmAkOiPbW4NwtTKB17//EQCxaH7TkdOvoEZHqfs2W50U7IKi+TuDkYOicoyUhILuDhOam78EH8W8ZeLA3kcffmjhFstyy5UnfKcD2KyWMdOC5w+A76At"
"DuxD9OnHVk44ue3prq+9A74B/rMDiD+xgOR/hr/hHfDRY3r9AOLpXnrCy/fBa6/fq8XrzfYOoEb7bAgac99+SBka2AfG2oDXJ9wtBhWWDRK1rnUtypzXHh9A5L3omRXQ"
"W91fMc0FolzmLRdbiBe415AbufdRj7SysHMA2j9nmqbXc0JdEBfsI56Ac0aOe9XKBFYhcsECup4zrNMfCUz0A6DtQQ9lnfdN0gQwdmXK+X3k3Bbz9gPzDWIdwg8yP4DH"
"PWeMGlIci6A1tX8AoIA0Q0afQAHoNXkwStSUNYg5DU/IOVFwkBGKcTCALqhGZYD2efsRWMdGoTIdIFRzNi+s9+c5dCQ72tQOcr94ntNJos3HklpnTdz/CGC9vECfGfCU"
"56b2NMcpyY42tYPaEPsfArePvhbgIk+aAzsHoLZEh61pzmDdnCj7gLCZu4u+353lmveFJU1roh9AviB1ARiCVXFvb+ZDTAaxmROOfANdDZzNCTGS09p41lSHB3CC6l9N"
"vhP9XvN9bzwFR/IVho5yxN4BXIFj2uCPod9rue9Tj6Hn3/kOuITmbh/YWzDdaxHPPQafvx+AcbDh7Rd8NfboAz86b9xaNw6g5lj5hQbxmmKDMllpfc5f9Q3dr5msNO9+"
"CBoLymSldW2+JgrxDrBP9oIR2MERKmgL22TPO5y76mGMWjewW0oxP88Gdsl9tpwN9j4CPwrbd8Ad1h8FDCjJPfbcEZdUKuOcjdDDeCS8bmR8B9B7kCM5aO/z1cTIKJyC"
"bwUWL97NwFLeKv6XotuBiwiaPG24y1cTkRksSt8OL70Z+QcY/NoBBK74aiIyY2Ret2IkUVRz72YEPXkASPH4oXH/Q8aKY8ZUVKCqL6Mylk29vRhJNEX9H009xHn7a76a"
"iFzxwAHkc9xb03OLr/QdQNH1vXj0AHxwiC9xACicgm8FFi/eScw5/ee/A5RBlnvsuSMuqVTGOQsh781bQgRH+cpvgt7qr8ZLvwp/hxN44QD8zvq78dI74Dvg9wD6Ozm/"
"NqFW5LfpjKv1V/0Vj84bN9a1kcR4B/SFzMnhhOixQZmstD7nr/qG7tdMVpp3PwSNBWWy0ro2XxMD8uMjYJ+sRgR2cIQK2sI22fMO5656RFKtGzCb1YuYn2cDu+Q+W45z"
"+l/hO8CP9CieW7eswkeA3k0eycVuf+VF7nBc1BeDM49CBON+YNya7wA4t3lkXrfC+YyjejSMvd4D8doBSJ2G8xFHfi7y4J46QIU+AkPcZdAo4NlOf8tRYfCAIz8Thu/z"
"ZDz8t0FeuDHuf8lXE5Gficp8oifjtQNwWO/x1UTkZ6LnF+KpjwACethXHBTFEdccw/qShZDpR3HGTUrzS/A5cJ+/CDoAioFXD+BvOwE+bj00qhcOQO+kvwR+4/sArF96"
"BwjnBxHdPrHqd2O7/+ndtgdw4wHX/ZfxjbyYP0cMrxuo2MfF/Zb98O8B68S8wQbZxqCj/OwL1Z3n9hG3nyYWebW+36WH8yAVwPFHoBYeYm5fPeimv8XZQPTm/sV26/0W"
"rf3iAOhH31VkGCpAxupLR1Kx27dOCQO/U0hHRR3Oyh6ExApna6K0XMlIKtwOHgdgw7jQIbrxhLaMsmsUKYR36O4tun4VHkn0JzVffWrXAcq3aBUwFt0OAF4bONG9fkYr"
"glaP5uJ/UL92AM+ygpSFI5x36iGOdfsxKAad6lj+GitgNZ3BufV+T+v0d3S9A54J3uhpDavpDM+9i0/itQN4MoL2OCPwFI/Y80+ifQfUW+ZUgwc9y5a7elSg1oB8QdM4"
"5Ft/GeJGxV8Nt59vHRj69wBUnoPvmeKvhjvPN3pTV/rOAXjdye6fxSdvHAdwsb9Pzrwi7JMtonXSHjjvHt94RU7dGydODwCNSD1WDG96wHjcaW6RW9xoY+TuNhdzM/pH"
"YF14vtF2+vSNgN7cP5seWBdcHuRTGAeQGydNOrKj6Ziiw4JW6Ro44lGIVACeqVhkjw5rb7enGSPzCsx/GQocaXur7hXxkqZYRrqM2tFRmtWezopX4P5vgikJawwyS76m"
"LUIjJPuAeRMEq12dFTcZwQNIW7Hqs3B+E1NEdqRJGsm8CYLVnqY1qqgZdw6AR3+knd/EFJEdaZJ4dwjpZIHVTY0DmF7Qjj4N5zcxRWRHmqSRxHSLIwce0vUd8Gw4v4lH"
"4uVwOQ/sssDqpv4rD+AwCFY3tX4PCHHAVzFS0ht01DC6ij5GlPaDgw9y/00wTBXCqt8D73pj93nkE4+zdwB1n0/csXa9sfs8InV3/a25OgC+I1DM+v3wxhc3mB8glc3z"
"xXfn5nfAQ4iNrx7iD+D6MU67pwdw8fLmP6G72Dzwxtjgqrv2Z33+mGcHkOuOdoAd6ewOcf+pv5Hn61t3XpigW/vM8zt+x62PwO7KxPKC7qIeTNgYG1x11/6s958zfhGi"
"7+6kK/USWPrZifU1NSAN30Xzq8+AZgcoRSpNlE7a1ZFUqAHEO4B6ZPmsNExr4EJnFUUbe0Z3udd/p+4HYJuVElQ0bmgUFZCpYdzTxeo9GkDsd611ALhah1k+F13oKrL/"
"dBSVYFn1oYYoutL9AGCERAVLvuJUl5nlsxH7glLUY13qqCoHTnV+BHK99oMbJflau7B+IZK0f2gm8qkeYInVwJneOYDsMwU7zrQL6xei0dy7owO9d8H9SzByoOmRgh1n"
"2oX1C9Fo7j2ie32i+XsAzZU54fpKu7B2jAR6iEdVERaD7XM9CpRBsM51vAPeD96p+GtherqHDkArr1/WdIu34/ZjHKE/3iMHcPPGeouhAL8ZNx/jEPPj1T+KHuGq/zDy"
"gO5iHX/uaQ5ex3gHXD3Qjf7ezka0envVW2PBev9Ft+XLLhu5GMD8Y3Bv4sg1RnfaOe4zrVhkanGkeWBG9SufaRSzFsptnfYd4Ad7FrH8ZIflxhu9NRasz3f8vIu/kd3o"
"HwFSSFTpUtuzrn5GzjE454DR5le9hoF6pN7bD20Ida1RxP/T1ZBpAVJtLnOliVQCn9Dd2Otbdz9wrqF4AMByQpClpVjSlfMHIlLnvQiw5nNda2R8BEKZBlaDBXJVE304"
"8Kob74YepRcXGnn+KUCoSmPp6wB9kJE+HH7hfvWRVdbzSLXiQnMZfgqkMQ2Kqg0xsB37cMwHwIRcVdFtTeaPwcmysjm7A3M/6JMRSfXpATBXcaVVzD8FyFI2Z3dg7gd9"
"MiJN3PKqH2FV9XtAEHs1yirt9M2oauxTOq5i5UFZWEZ1l6MaiR+BGWwX/2nkfa8e4B0PuHcA//UJ3D2AtzzezgHoDZL855F3PnmE0XrL400HUPcl/wT0A9i+/uUkZuk/"
"g5F7I+pskHob2kNro/HcWpo3eKCVx2gHUC9ou6kaUNIOt2NZFmFn1xUxagyA5RGW4KU3N2/wQCuPUQcQ4z0a1p1WfY48kCtgbCRc6xrrB5jXBeIAdDff1IyCjUlavx2+"
"Ga/NfXD/YTlguAFyhM6Lpm2xnJHGAVCxw4pYdIh54MPYPk8x68otYCIJ2kftatGvA8hmLShmzw3y27C/ne6JShR5bnStgMk6KttTNH/nAKquji/NRLwPHzoAJttTNL//"
"t8FNkw1WEOVz7pPQvQq6PxmNytnIctP2Krrp93dAToBF8vmq0+eSj2JzHws+hKuNXtLI3KcHfcT2I9CiURR5AHI+C95LImBRjcpNLwl5jeY/cgBzvA/4A9pgcx+LalRe"
"dC+iXkPdiIOfAqxRtAg7+X3Y3y/MqYEby0SDsjhdhEqYDLpsSfcD+DwOb/THnmAHX+EA/svX/+//+L74M/iT97qL8Q742fj6BxDvmh7OG7as4g5+D0D8N+H0AEbmdRP9"
"7wJm7UWZnH7PIxXnYFIUolmDGT2PyGsE5sDVV7XD2eSV0HojZDPafx4fiHqNnlFpvVPnqyBYlTfpfqmFhMzqMWzWzZs8dAAo7McxOGAIlntBsCo/QINWXhxgQpZkM5cl"
"x1i0WIUh0YMN0uDpAFBG6tEyCvuhaSLFCKDeJpgCLOTnVVM7lvJZMG39i9B3QC6NTMPcfStFPSuNyKGXoE/VmP4IXvJTT1ZA+0Ry0FYtw7pF0OrRnN4BKvoArcwo7Ie2"
"6ZcYUG+KbEwFeCRe9R+/+UolnJJbb9UhU1/FSJHrADr3aBmFfYs0Bfd62CdmB69Xc3YyV0qO7OjahvWdGHjoADYRqfNRBMxbhxy5KtKkm9qLSKvXYyTRFPoOgDAzYAwy"
"954jUnEO2soIoI26nM6Rez+GscDL5KuRPks3SCnzoiFiQf4efxnSS9tF9Xanfg9A/Hfjxx/AC/gOfxtUIRmUHWKRE77RAYgiZweY1YIvfwD5euqF+QWZq3gC/e8CwqqN"
"o9sczT+Pvl3sjf2zUC52nw8ycfNRcLoz3gE0hBCTYeyah/YreGpHP0c+j4ru91CuA4gDITtCle55DSDXt8INUVSiwXGB12AnCtBInGPF5V2joCgeBQa737WqOABafQAO"
"7dIt9xhp13cwNd2yIq5Jy6yheX4TkcCay+LIr2IcgIwgBk+u+aya3YNp6/fo/Z4VcU16Y87za2jez0fOJkTzmzPS/LfBHm4s++3GI/2eFXFFgQaEzXDg5uxeeD7nstjz"
"swTdOYCSR6G5w+j9nhVxdZ+OWHaWO+H5nMti8XutfH4Aq9djJFGsnntr9H7PiriiQAPCZjisz4LDo/a+WSx+D2V8B6DKhjSK5leMHAWTjOJIjNlPRhdU/igc1iHAYYgO"
"OC7IzjJBgOyF8WMwh3L4BHszV97FvmhH0tz59CO4uPHA7wFEyrHr+d2R3WXNvNoW/UgavBi/Db3XT8F3wA8GfwrcOKmA/4BAD6x7CJ/a9wCPHEBOsfC36bvxqX338fsR"
"mE4chfRIKaW7Ce5RmQtEqW2AsJwXDK+W1XkEBrqvOokeaMdn9Nwi3gFsBGTCMCuDYkdIcY+RRDG99LZ6UF4Z1mbfzxGp67PomcEHXOLWAXih/bDE+8FlVzr3beF9wVFK"
"2zu/b4+eR+QFKv/mO4ACGiyxH9GdvcCqR9FKBJyJqwdt8yoIVvLyWvyDAwDjObqJOTCvi+ACJHH3UagTDImrMfyM9JvXAjZqgpX6eS3+0TsgV0xmDLa7S5eseo7AVnOe"
"NTSK4rjco2XzKLwXoYq3GcGLu7A7og5ARkRcyc3MYKryKjw86aiaBz+sxmtEWr0egartsIhzcK/FKweANPlHsc5R5pVhbV4j0ur1CFTdnWL3FeMAeDBmBgs2UrAujiLK"
"QI5R2+dojQ2RpAuG52Q1tpx81bbKC8i3Y1XaAcQ74FXkHc5Qd/9K+IMH8FXxjgP4q/F7AOIfi693APyGlvg8fg8gbzgCP2TFA5wA0yfYYrBHblj1Q9hu90k8fgDBlHkh"
"En/2BTyCvcc6PAB4AfCiKfNCjCTCGKTtKsRBedlmWnkEBrqvOokeaMdneGCJxw8gQJkXQv4I3Cf9uTfFtJ5hvTIjUtdn0bMCi5uOODuAuH34MqVVOFsDlNvY6420roMx"
"cfXCVHRvPwhWzfdiNOSNnwJhtIHGDgxYa9O8TCN5HwUke+L04YnEcHE1hp+RfvN2g2DVfKxffP4YlNANzg8gvbouo90j9SjwQlhCoiiOyz1aNq+CYNV8L0ZD3n93AIM3"
"663Na0RavaPoWYHFTUf0AwBmRg8iNY1wonIh3zzJkSQHqp+XtNLClpOv2paC2j5dUPmYcwAHvwlq7Rvhh4D4BE62dms78Z5/D/gaOD6A7OxNfPsDiLe5yl18nwN4Et/4"
"ALZ/8pMD8c7vgJO32sW78Da4j3aLvO47a8/ZbMWooN76Jaj9c/PCIg3abf5gLjGNtXWJ3Q22Znfe+RHgvpEdRL9fxzyfxoIys2Ix/hz7fEgbwagrHemPfQf053kFt/fp"
"Q1HrBdIYONBP/4sQtAobHEkZQu21P4oug1djJDOwmsFrBGJ56pEu+Ol/EYJlfz+4BdK8TuidKkZauPaJauY5Ao0xdMFP/4MILPtX4TWddxwUI63ssMaRyJsi0BhDF/z0"
"P4ik3/XMFW0ZCzmgZBYjYSDGyI7IYl6bYD/Zc2c8vgRjR27QG3E5fE+ENoePVHPZM+/5AdabDoqR4ursCBqpxBoBcxTyq9hq/hTojcaO6QBarHO5l3n1e70qFyPF1XkT"
"kVYvImCOAvU59wMAZkYPIjUNr6mwb556gfQbo0+G5WBhzqCZkypZQKjlQgNnfPB7ACZex4PbPHpXzb/0sB/7RQj47AF4/MseAN+id8E38m08OH6Iz74D/gDiIAKSD6Md"
"wHtO9GW89nqOcbBvfwew/ZG7PwA+BBIfZNA7Hqn2JfQ6+ZvgdId33O0F4O5MfJBB73ik2hfwrnUAwaiVb0CD63uGOhIj9u4TFpOZgMnEPtajmhHerq+7BUfFXPvaDd0/"
"At29B0/zBoW8AfxQ84TFZCZgVgLtDW73HQgNX3VZuaW0r+07wHGNvP0yDlnPF2masJjMBMxKoL3BvQOAhG+RlFum5hwOAFU0elzDt99Mc4vYUnv1iWHKJ8/doTJtMI3H"
"Ym1gZD8KbI+RoKHRKx1qcB0AWnJV2A24wMrX4E3Ey66od2+zWZcOsfglyUrWqtoBqBWZ1afg3cV3D6CmWEXqc9MuIbGxSKNNa/4LHMByN4jd++/PGxtXRq5SarvESYyf"
"AqhkKbN6FDrZA0SXExwbNSWBLi4oeCu8EELjRiuFeXo6gBG+tgcwSMWjOF8XXU54bBpHFxcUvHNw/BhsxqvBbXNfShTj6r8KJ872xXYDkhPO1rGLCY8dbJLpvdjuO+6/"
"fwD7D3aN83XR5YTn9uePz/c17OwbenMAm6kF0Q9I/vXY/Qj8JMQB8I9z/YM90kd8hbtzj8L7mjtu3G8cQCweFWbbgiN9xFe4PbfzQgrbhvc1N2yHt/gvD0Avc3m5nts9"
"iI2uH5vmhnV6DziAWhs/GOK2bWM4KiMd8RVqTi9L+6IS92RzwuqNoZwXN6zTe9gcAPaMR2uaYX3AV8g5vfC4jdfBiEZklPZmbCxvEfPihu242BjL4wBoewPs2Td2WB9w"
"QRsmqJ3a5prTiQRHRgkZVcfGqK3UjOTtZDUsO2KO3wGQmQjrmEJYH/BIyLEvizKQK23aqMQcUWOGdPl9PllBFXkoXHwws4b0L0IDINUBay9IfcDeiHdDKUu50qaLaiTU"
"MCPZ5v1twkDmgFvJCirUXk83AfvOAUCWPmIiBK1VV1I5eFShHLKiiUwSLLQrZkfBurGCqoCnQY9M7+ZHQCX1AedgFajyhcIoPQiDmFG4pYScSCU/ZkfF0cYKqsgepFzA"
"A4gW2m3G2mtTH/BIyMUq/EJRl642CyeaNgqzCsz7JiuoULfB0AEXcQAar0Sk9rz0ERe4X2HdXxpgUboOgG5iVkBMqxHzZgXVJeIACG9gHOkjvsKjc8sBHCLnUyTu7NAO"
"gH8AiSN9xFd4dM58Bc+ZG26sbgfw7XDn9L71AdzDnQPgUe68xSa4bzZW/Spe3c/rxQ8cQKZ9uL/OrXpgVg9iZ7+H4PXi/+IA9KPuSWz3ewxeL/46B6C35CVyvxz3qoUx"
"g0I+C1rJ4wCyT28LDijhMWtJwUM5F4zSqW3kZoP3NScsxaxDMrJPlTqyK/ijwDpW5ngH1AbkhAxlJo0iT/CQ53JXJzuoUXgCHKlHZqVYjl5qReQw2U6OjEo6rLg4gysS"
"PwJaQU5gtZjVSJygrQZZfXO43Z91ZAs14IOHUo+SHn224Ckqex8OUauIgWhFNytwvQOcYp4rcp1mkehFzjHJVo/kbvp9PgL1yGFHx71wIDgDe5BBA/1QyZE7bIhjkNtx"
"Da5I9R0AwgLIAToeUGIXHe07EmSrR8pt7EfOeoQsbBM7RbOHMu6ILqdChuE+srodYYLAHMRi1sn8CAQ0TAZqHZipRNsYEnWxseoQIWnlk4uHIxbgwIXSA9CBmaGmmQPi"
"IrQ4B8Y7AC1NhS1MwgswPXcI9ZONVYdID8H9QNMc4Vn3rcNxrmpmFu6KlcT9HQBIBSaRC4/g/jq36gEp342Mu89zhG0xaxqR0weKw0KuOZKSuA5gC60QvPAI7q9zq34V"
"r+7n9eIHDqBOdhfum41Vv4pX9/N68f0D+KY4O4AfgfjvAngr/FSMAwj6PQCIn4h2AP4k/KyPRB1AvOgePwTzAaD8oQeAN75f/E88AL/wPIgfgt/vgN8DwGtdXvxPPQB8"
"+M0/BHUAPxTjAADJn4cf/tfhf//9Pw4TaU54zj6EAAAAAElFTkSuQmCC";

// See http://en.wikipedia.org/wiki/WGL4
static const std::string kDefaultFontCodepage =
// C0 Controls and Basic Latin
"0x0020-0x007F,"
// C1 Controls and Latin-1 Supplement\n"
"0x00A0-0x00FF,"
// Latin Extended-A
"0x0100-0x017F,"
// Latin Extended-B
"0x0192, 0x01FA-0x01FF,"
// Spacing Modifier Letters
"0x02C6, 0x02C7, 0x02C9, 0x02D8-0x02DD,"
// Greek
"0x037E, 0x0384-0x038A, 0x038C, 0x038E-0x03A1, 0x03A3-0x03CE,"
// Cyrillic
"0x0400-0x045F, 0x0490-0x0491,"
// Latin Extended Additional
"0x1E80-0x1E85, 0x1EF2-0x1EF3,"
// General Punctuation
"0x2013-0x2015, 0x2017-0x201E, 0x2020-0x2022, 0x2026, 0x2030, 0x2032-0x2033, 0x2039-0x203A, 0x203C, 0x203E, 0x2044,"
// Super/subscript
"0x207F,"
// Currency symbols
"0x20A3-0x20A4, 0x20A7, 0x20AC,"
// Letterlike symbols
"0x2105, 0x2113, 0x2116, 0x2122, 0x2126, 0x212E,"
// Number forms
"0x215B-0x215E,"
// Arrows
"0x2190-0x2195, 0x21A8,"
// Mathematical operators
"0x2202, 0x2206, 0x220F, 0x2211-0x2212, 0x2215, 0x2219-0x221A, 0x221E-0x221F, 0x2229, 0x222B, 0x2248, 0x2260-0x2261, 0x2264-0x2265,"
// Miscellaneous technical
"0x2302, 0x2310, 0x2320-0x2321,"
// Box drawing symbols: provided by dynamic tileset
// Block elements: provided by dynamic tileset
// Geometric shapes
"0x25A0-0x25A1, 0x25AA-0x25AC, 0x25B2, 0x25BA, 0x25BC, 0x25C4, 0x25CA-0x25CB, 0x25CF, 0x25D8-0x25D9, 0x25E6,"
// Miscellaneous shapes
"0x263A-0x263C, 0x2640, 0x2642, 0x2660, 0x2663, 0x2665-0x2666, 0x266A-0x266B,"
// Private use area
"0xF001-0xF002,"
// Alphabet presentation form
"0xFB01-0xFB02";

struct BuiltinResource
{
	BuiltinResource(const std::string& data, bool base64encoded) :
		data(data),
		base64encoded(base64encoded)
	{ }

	const std::string& data;
	bool base64encoded;
};

static std::map<std::wstring, BuiltinResource> kBuiltinResources =
{
	{ L"codepage-ascii", BuiltinResource(kCodepageASCII, false) },
	{ L"codepage-437", BuiltinResource(kCodepage437, false) },
	{ L"codepage-866", BuiltinResource(kCodepage866, false) },
	{ L"codepage-1250", BuiltinResource(kCodepage1250, false) },
	{ L"codepage-1251", BuiltinResource(kCodepage1251, false) },
	{ L"tileset-default", BuiltinResource(kDefaultFont, true) },
	{ L"codepage-tileset-default", BuiltinResource(kDefaultFontCodepage, false) },
	{ L"codepage-tcod", BuiltinResource(kCodepageTCOD, false) }
};

struct MemoryResource
{
	MemoryResource() :
		address(0),
		size(0)
	{ }

	uint64_t address;
	size_t size;
};

bool try_parse(const std::wstring& s, MemoryResource& out)
{
	size_t colon_pos = s.find(L":");
	if (colon_pos == std::wstring::npos)
		return false;

	if (!try_parse(s.substr(0, colon_pos), out.address))
		return false;

	if (!try_parse(s.substr(colon_pos + 1), out.size))
		return false;

	return true;
}

std::vector<uint8_t> Resource::Open(std::wstring name, std::wstring prefix)
{
	LOG(Debug, "Requested resource \"" << name << "\" with possible prefix \"" << prefix << "\"");

	auto i = kBuiltinResources.find(prefix + name);
	MemoryResource mem;

	if (i != kBuiltinResources.end())
	{
		LOG(Debug, "Resource \"" << prefix << name << "\" is built-in");

		if (i->second.base64encoded)
		{
			return Base64::Decode(i->second.data);
		}
		else
		{
			auto data = (const uint8_t*)i->second.data.data();
			return std::vector<uint8_t>(data, data + i->second.data.length());
		}
	}
	else if (name.find(L"text:") == 0)
	{
		std::string text = UTF8Encoding().Convert(name.substr(5));
		std::vector<uint8_t> result(text.length());
		memcpy(&result[0], (uint8_t*)text.data(), text.length());
		return result;
	}
	else if (try_parse(name, mem))
	{
		// Memory source.
		LOG(Debug, "Loading resource from memory '" << name << "'");
		std::vector<uint8_t> result(mem.size);
		memcpy(&result[0], (uint8_t*)mem.address, mem.size);
		return std::move(result);
	}
	else
	{
		return ReadFile(name);
	}
}