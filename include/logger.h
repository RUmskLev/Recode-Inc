#ifndef LOGGER_H
#define LOGGER_H

#include <string>


/**
 * @brief Used to define a level for logger.
 * Colors used in each level:
 *      L_DEBUG - Blue.
 *      L_INFO - White.
 *      L_WARNING - Yellow.
 *      L_ERROR - Red.
 * 
 */
enum LogLevel { L_DEBUG, L_INFO, L_WARNING, L_ERROR };

enum LoggerMode { LMode_Console, LMode_File };

/**
 * @brief A logger instatnce. Use methods of Logger class to log colored info, debug, errors and warnings.
 * Really logs anything only if "_DEBUG" preprocessor defenition is set.
 * 
 */
class Logger
{
public:
    /**
     * @brief Construct a new Logger object that outputs everything to created console window.
     * 
     */
    Logger();

    /**
     * @brief Destroy the Logger object that was created to output messages in console window.
     * 
     */
    ~Logger();

    /**
     * @brief Log message with provided level in white color.
     * 
     * @param level instatnce of LogLevel, defines level of message.
     * @param message contains of log message.
     */
    void log(LogLevel level, const std::string& message);

    /**
     * @brief log message with level DEBUG, colored in blue.
     * 
     * @param message contains of log message.
     */
    void debug(const std::string& message);

    /**
     * @brief log message with level INFO, colored in white.
     * 
     * @param message contains of log message.
     */
    void info(const std::string& message);

    /**
     * @brief log message with level WARNING, colored in yellow.
     * 
     * @param message contains of log message.
     */
    void warn(const std::string& message);

    /**
     * @brief log message with level ERROR, colored in red.
     * 
     * @param message contains of log message.
     */
    void error(const std::string& message);

private:
    /**
     * @brief Converts LogLevel enum values to it's human readable variations
     * 
     * @param level Logger level, element of LogLevel enum
     * @return std::string 
     */
    std::string levelToString(LogLevel level);
    /**
     * @brief Returns formatted current time and date
     * 
     * @return char
     */
    char getCurrentTime();
};
#endif