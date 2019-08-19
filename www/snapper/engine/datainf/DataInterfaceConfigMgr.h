#ifndef _DataInterfaceConfigMgr_H_
#define _DataInterfaceConfigMgr_H_

#include <vector>
#include <map>
#include <set>
#include <string>
#include <boost/noncopyable.hpp>


using namespace std;

namespace snapper { namespace datamgr
{


class DataInterfaceConfigMgr : private boost::noncopyable
{
public:
    DataInterfaceConfigMgr();

    ~DataInterfaceConfigMgr();

    static DataInterfaceConfigMgr* get();

    bool  initialize();

private:
    bool   isready;
};


}}

#endif //  _DataInterfaceConfigMgr_H_
