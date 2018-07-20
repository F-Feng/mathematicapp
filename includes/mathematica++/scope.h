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

#ifndef SCOPE_H
#define SCOPE_H

#include <list>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace mathematica{
class connector;
    
namespace detail{
    
struct scope: public boost::enable_shared_from_this<scope>{
  friend class mathematica::connector;
  public:
    typedef boost::shared_ptr<scope> scope_ptr;
    typedef std::vector<std::string> cache_collection_type;
    typedef std::list<scope_ptr> scope_collection_type;
    typedef scope_collection_type::iterator iterator;
    typedef scope_collection_type::const_iterator const_iterator;
  private:
    connector&             _connector;
    scope*                 _parent;
    std::string            _name;
    cache_collection_type  _cache;
    scope_collection_type  _children;
    
    scope(connector& conn, scope* parent=0x0, const std::string& key="");
  public:
    ~scope();
  public:
    std::string name() const;
    bool is_root() const;
    const_iterator begin() const;
    const_iterator end() const;
    size_t locals_count() const;
    boost::shared_ptr<scope> parent();
    boost::shared_ptr<const scope> parent() const;
    
    /**
     * ceates a child scope under its parent
     */
    scope_ptr create(const std::string& key="");
    /**
     * adds a key in the current scope (saved in mathematica runtime cache)
     */
    void add(const std::string& key);
    /**
     * unset this scope and all its children recursively and unsets them from mathematica Runtime
     */
    void unset(const std::string& name="");
    /**
     * delete's all child scopes recursively and also unsets them from Mathematica Runtime but keeps the locals
     * \return the number of elements removed (including children of children recursively)
     */
    void unset_child_scopes();
    void remove_child_scope(scope_ptr child);
    /**
     * finds the scopeby scope name or by a saved key name in the tree (recursively)
     */
    boost::shared_ptr<const scope> find(const std::string& key) const;
    boost::shared_ptr<scope> find(const std::string& key);
    /**
     * checks whether a key (scope name or saved variable name) exists in the tree or not
     */
    bool exists(const std::string& key) const;
};

}
}

#endif // SCOPE_H
