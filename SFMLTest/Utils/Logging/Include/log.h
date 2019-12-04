//
// Created by marco on 03.12.19.
//

#ifndef SFMLTEST_LOG_H
#define SFMLTEST_LOG_H

#include <string>
#include <memory>
#include <fstream>
#include <mutex>
#include <sstream>
#include <iostream>

//based on https://www.drdobbs.com/cpp/a-lightweight-logger-for-c/240147505
namespace logging {

    enum logmsg_type {
        debug = 1, warning, error
    };

    template<typename log_policy>
    class logger {
    public:
        logger(const std::string &name){
            log_line_number = 0;
            policy = new log_policy;
            if(!policy)
                throw std::runtime_error("LOGGER: Unable to create logpolicy object");
            policy->open_ostream(name);
        }

        ~logger(){
            if(policy){
                policy->close_ostream();
                delete policy;
            }
        };
//todo mach das nicht mit preprocessor, überlade methoden (ähnlich zu dem github example)
        template<logmsg_type level, typename ...Args>
        void print(Args...args){
            write_mutex.lock();
            switch (level) {
                case logmsg_type::debug:
#ifndef LOGGING_FILE
                    log_stream << "\033[1;32m<DEBUG>\033[0m: ";
#else
                    log_stream << "<DEBUG> : ";
#endif
                    break;
                case logmsg_type::warning:
#ifndef LOGGING_FILE
                    log_stream << "\033[1;33m<WARNING>\033[0m: ";
#else
                    log_stream << "<WARNING> : ";
#endif
                    break;
                case logmsg_type::error:
#ifndef LOGGING_FILE
                    log_stream << "\033[1;31m<ERROR>\033[0m: ";
#else
                    log_stream << "<ERROR> : ";
#endif
                    break;
            }
            print_impl(args...);
            write_mutex.unlock();
        }

    private:
        unsigned int log_line_number;

        std::string get_logline_header(){
            std::stringstream header;
            header.str("");
            header.fill('0');
            header.width(7);
            header << log_line_number++ << " < " << get_time() << " - ";
            header.fill('0');
            header.width(7);
            header << clock() << "> ~ ";
            return header.str();
        }
        std::string get_time(){
            std::string time_str;
            time_t rawtime;
            time(&rawtime);
            time_str = ctime(&rawtime);
            //delete newline character at the end
            return time_str.substr(0,time_str.size()-1);
        }


        std::stringstream log_stream;
        //todo remove rawpointer, no need for it
        log_policy *policy;
        std::mutex write_mutex;

        void print_impl(){
            policy->write(get_logline_header() + log_stream.str());
            log_stream.str("");
        }

        template<typename First, typename ...Rest>
        void print_impl(First parm1, Rest...rest){
            log_stream<<parm1;
            print_impl(rest...);
        }
    };


    class log_policy_interface {
    public:
        //=0 defines a pure virtual function!
        virtual void open_ostream(const std::string &name) = 0;

        virtual void close_ostream() = 0;

        virtual void write(const std::string &msg) = 0;
    };

    class file_log_policy : public log_policy_interface {
    public:
        file_log_policy() : out_stream(new std::ofstream) {}

        void open_ostream(const std::string &name) override{
            out_stream->open(name.c_str(), std::ios_base::binary | std::ios_base::out);
            if (!out_stream->is_open()) {
                throw (std::runtime_error("LOGGER: Unable to open outputstream"));
            }
        }

        void close_ostream() override{
            if(out_stream->is_open()){
                out_stream->close();
            }
        }

        void write(const std::string &msg) override{
            (*out_stream) << msg << std::endl << std::flush;
        }

        ~file_log_policy(){
            if (out_stream->is_open()) {
                out_stream->close();
            }
        }

    private:
        std::unique_ptr<std::ofstream> out_stream;
    };

    //Todo fix use of strings
    class console_log_policy : log_policy_interface{
    public:
        console_log_policy() : out_stream(new std::ostringstream){}
        void open_ostream(const std::string &name){
            /* nothing to do in here*/
        }

        void close_ostream(){
            /* nothing to do in here */
        }

        void write(const std::string &msg){
            //(*out_stream) << msg << std::endl << std::flush;
            std::cout << msg << std::endl;
        }
        ~console_log_policy(){
            //(*out_stream) << "End of logging stream" << std::endl << std::flush;
        }


    private:
        std::unique_ptr<std::ostringstream> out_stream;
    };

#endif //SFMLTEST_LOG_H
}