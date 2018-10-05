#include "mathematica++/transport.h"

mathematica::basic_transport::basic_transport(WMK_LINK link): _link(link), _connection(driver::link(link)), _shell(_connection){
    
}

mathematica::value mathematica::basic_transport::recv(){
    mathematica::value val;
    _shell >> val;
    return val;
}

mathematica::transport::transport(WolframLibraryData data): _data(data), _io(data->getWSLINK(data)){
    
}

mathematica::wtransport::wtransport(WolframLibraryData data, mathematica::transport::link_type link): transport(data), _control(link){
    mathematica::value input = _control._connection->fetch_token(&_control._shell);
    _input = boost::dynamic_pointer_cast<mathematica::tokens::function>(input);
}
