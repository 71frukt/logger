#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H

#define CONSOLE_BLACK   "30" 
#define CONSOLE_RED     "31"
#define CONSOLE_GREEN   "32"
#define CONSOLE_YELLOW  "33"
#define CONSOLE_BLUE    "34"
#define CONSOLE_MAGENTA "35"
#define CONSOLE_CYAN    "36"
#define CONSOLE_WHITE   "37"

#define HTML_BLUE    "blue"
#define HTML_CYAN    "cyan"
#define HTML_SKYBLUE "SkyBlue"
#define HTML_RED     "red"
#define HTML_GREEN   "green"
#define HTML_YELLOW  "yellow"
#define HTML_WHITE   "white"
#define HTML_MAGENTA "Fuchsia"

#define CONSOLE_COLORED(STR, COLOR) "\x1b[" COLOR "m" STR "\x1b[0m"

#define HTML_COLORED(STR, color)  "<span class=" color ">" STR "</span>"



#define COLORS_HTML_PREAMBLE                                                                                                               \
    "\tbody { background: linear-gradient(to right, #0f2027, #203a43, #2c5364);}                                         \n"          \
    "\tpre { color: #ffffff; }                                                                                               \n"           \
    "\t." HTML_RED     "{ color:" HTML_RED     ";}                                                                             \n"            \
    "\t." HTML_YELLOW  "{ color:" HTML_YELLOW  ";}                                                                             \n"             \
    "\t." HTML_BLUE    "{ color:" HTML_BLUE    ";}                                                                             \n"              \
    "\t." HTML_GREEN   "{ color:" HTML_GREEN   ";}                                                                             \n"               \
    "\t." HTML_CYAN    "{ color:" HTML_CYAN    ";}                                                                             \n"                \
    "\t." HTML_MAGENTA "{ color:" HTML_MAGENTA ";}                                                                             \n"                 \
    "\t." HTML_SKYBLUE "{ color:" HTML_SKYBLUE ";}                                                                             \n"                  \
    "\t.jumbotron {                                                                                                            \n"                   \
    "\t\tbackground: linear-gradient(to bottom, #ffffff,  #ffffff, #001aff, #001aff, #b00000, #b00000);            \n"                    \
    "\t\tcolor: white;                                                                                                         \n"                     \
    "\t\ttext-shadow: 1px 1px 2px rgba(0,0,0,0.5);                                                                           \n"                      \
    "\t\tborder-radius: 0;                                                                                                     \n"                       \
    "\t\tmargin-bottom: 0;                                                                                                     \n"                        \
    "\t}                                                                                                                       \n"                         \
                     


#define TABLE_HTML_COLOR                                  \
    "\ttable {                                      \n"    \
    "\t    width: 85%%;                             \n"     \
    "\t    margin-left: 3%%;                        \n"      \
    "\t    border-collapse: collapse;               \n"       \
    "\t}                                            \n"        \
    "\t                                             \n"         \
    "\ttable td {                                   \n"          \
    "\t    color: #00ccff;                        \n"           \
    "\t    border: 1px solid #3a4a5a;             \n"            \
    "\t    padding: 5px 10px;                       \n"             \
    "\t}                                            \n"              \
    "\t                                             \n"               \
    "\ttable tr:first-child td {                    \n"                \
    "\t    color: #ffffff;                        \n"                 \
    "\t    font-weight: bold;                       \n"                  \
    "\t    background-color: rgba(0,0,0,0.2);     \n"                   \
    "\t}                                            \n"                    \
    "\t                                             \n"                     \
    "\ttable td:first-child {                       \n"                      \
    "\t    color: #ffffff;                        \n"                       \
    "\t}                                            \n"                        \


void ConsoleColoredFprint(const char *const color, const char *const format, va_list args);
void HtmlColoredFprint(FILE *dest_file, const char *const color, const char *const format, va_list args);

#endif