#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "logger.h"
#include "text_color.h"

FILE *LogFile = NULL;

FILE *OpenLog(const char *const logfile_name)
{
    LogFile = fopen(logfile_name, "w");

    assert(LogFile && "Error when opening LogFile");

    if (LogFile == NULL)
        fprintf(stderr, "Error when opening LogFile\n");

    fprintf(LogFile, "<html>                                                                                                                    \n"
                     "\t<head>                                                                                                                  \n"
                     "\t<title>%s</title>                                                                                                       \n"
                     "\t<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css\">                \n"
                     "\t</head>                                                                                                                 \n"
                     "\t<body>                                                                                                                  \n"
                     "\t<div class=\"jumbotron text-center\">                                                                                   \n"
                     "\t\t<h1>%s</h1>                                                                                                           \n"
                     "\t</div>                                                                                                                  \n"
                     "\t<pre>                                                                                                                   \n"
                     "\t<style>                                                                                                                 \n"
                     "\tbody { background: linear-gradient(to right, #0f2027, #203a43, #2c5364);}                                         \n"
                     "\tpre { color: #ffffff; }                                                                                               \n"
                     "\t." HTML_RED     "{ color:" HTML_RED     ";}                                                                             \n"
                     "\t." HTML_YELLOW  "{ color:" HTML_YELLOW  ";}                                                                             \n"
                     "\t." HTML_BLUE    "{ color:" HTML_BLUE    ";}                                                                             \n"
                     "\t." HTML_GREEN   "{ color:" HTML_GREEN   ";}                                                                             \n"
                     "\t." HTML_CYAN    "{ color:" HTML_CYAN    ";}                                                                             \n"
                     "\t." HTML_MAGENTA "{ color:" HTML_MAGENTA ";}                                                                             \n"
                     "\t." HTML_SKYBLUE "{ color:" HTML_SKYBLUE ";}                                                                             \n"
                     "\t.jumbotron {                                                                                                            \n"
                     "\t   background: linear-gradient(to bottom, #ffffff,  #ffffff, #001aff, #001aff, #b00000, #b00000);           \n"
                     "\t   color: white;                                                                                                        \n"
                     "\t   text-shadow: 1px 1px 2px rgba(0,0,0,0.5);                                                                          \n"
                     "\t   border-radius: 0;                                                                                                    \n"
                     "\t   margin-bottom: 0;                                                                                                    \n"
                     "\t}                                                                                                                       \n"
                     "\t</style>                                                                                                                \n"
                    , logfile_name, logfile_name);


    atexit(CloseLogFile);

    return LogFile;
}

void CloseLogFile()
{
    fprintf(LogFile,    "\t\t</pre>     \n"
                        "\t</body>      \n"
                        "</html>");

    assert(fclose(LogFile) != 0 && "Error when closing LogFile");
}

void LogPrint(const char *const file, const int line, const char *const func, LogType log_type, const char *const format, ...)
{   
    va_list args;
    va_start(args, format);


    switch (log_type)
    {
    case LogType::INFO:
        ON_LOGS(
        fprintf(LogFile, format, args);
        );
        break;
        
    case LogType::DUMP:
        ON_LOGS(
        fprintf(LogFile, "\t" HTML_COLORED("Dumped", HTML_SKYBLUE)  " from "  HTML_COLORED("%s:%d(%s)", HTML_CYAN)   "\n", file, line, func);
        fprintf(LogFile, format, args);
        );
        break;
        
    case LogType::ASSERT:
        ON_LOGS(
        fprintf(LogFile, "\t" HTML_COLORED("Assertation failed", HTML_MAGENTA) " in "    HTML_COLORED("%s:%d(%s)", HTML_CYAN)    "\n", file, line, func);
        HTML_COLORED_FPRINT(LogFile, HTML_MAGENTA, format, args);
        );

        fprintf(stderr, CONSOLE_COLORED("Assertation failed", CONSOLE_MAGENTA) " in " CONSOLE_COLORED("%s:%d(%s)", CONSOLE_CYAN) "\n", file, line, func);
        CONSOLE_COLORED_FPRINT(CONSOLE_MAGENTA, format, args);
        break;
        
    case LogType::ERROR:
        ON_LOGS(
        fprintf(LogFile,"\t" HTML_COLORED("Error", HTML_RED)    " in "    HTML_COLORED("%s:%d(%s)", HTML_CYAN)    "\n", file, line, func);
        HTML_COLORED_FPRINT(LogFile, HTML_RED, format, args);
        );

        fprintf(stderr,   CONSOLE_COLORED("Error", CONSOLE_RED) " in " CONSOLE_COLORED("%s:%d(%s)", CONSOLE_CYAN) "\n", file, line, func);
        CONSOLE_COLORED_FPRINT(CONSOLE_RED, format, args);
        break;

    case LogType::WARNING:
        ON_LOGS(
        fprintf(LogFile,"\t" HTML_COLORED("Warning", HTML_YELLOW)  " in "     HTML_COLORED("%s:%d(%s)", HTML_CYAN)    "\n", file, line, func);
        HTML_COLORED_FPRINT(LogFile, HTML_YELLOW, format, args);
        );

        fprintf(stderr,   CONSOLE_COLORED("Warning", CONSOLE_YELLOW) " in " CONSOLE_COLORED("%s:%d(%s)", CONSOLE_CYAN) "\n", file, line, func);
        CONSOLE_COLORED_FPRINT(CONSOLE_YELLOW, format, args);
        break;

    default:
        break;
    }

    fflush(LogFile);

    va_end(args);
}