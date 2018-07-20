/*
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * 
 */

#ifndef WSTP_CONNECTION_H
#define WSTP_CONNECTION_H

#include "wstp.h"
#include <string>
#include <stack>
#include <boost/shared_ptr.hpp>

namespace mathematica{
class token;
struct packet;
class accessor;
namespace driver{
namespace ws{

/**
 * no header should include this file, this should only be forward declared inside other classes of mathematica++
 * however this file can be included inside any cpp of mathematica++, but not usable for usercode, usercode should
 * have connector, wrapper etc.. as the interface to connection
 */
struct connection{
  typedef WSLINK link_type;
  typedef WSENV  env_type;
  typedef WSMARK mark_type;
  
  connection();
  connection(int argc, char** argv);
  connection(const std::string& name);
  
  std::string link_name() const;
  bool connected() const;
  
  void function(const std::string& name, unsigned int nargs);
  void integer(int n);
  void uinteger(unsigned int n);
  void long_integer(long n);
  void real(double n);
  void str(const std::string& s);
  void symbol(const std::string& s);
  void evaluate(std::string expression);
  void end();
  
  std::pair<std::string, int> get_function();
  int get_integer();
  double get_real();
  std::string get_str();
  std::string get_symbol();

  void disconnect();
  
  int next(mathematica::accessor* accessor);
  
  void pull();
  
  void flush();
  
  int head(std::string& type, int& nargs);
  int test(std::string head, int& nargs);

  std::string error(int& code);
  private:
    boost::shared_ptr<mathematica::token> fetch_token(mathematica::accessor* accessor);
  public:
    boost::shared_ptr<mathematica::packet> fetch_packet(mathematica::accessor* accessor);
    boost::shared_ptr<mathematica::packet> ignore_packet(mathematica::accessor* accessor);
  public:
    void push();
    void pop();
  private:
    bool _connected;
		link_type _link;
		env_type  _env;
    std::stack<mark_type> _checkpoints;
		
		connection(connection& other);
};

}
}
}

#endif // WSTP_CONNECTION_H