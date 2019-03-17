/*
   ||
   || @file 	MenuBackend.h
   || @version 1.6
   || @author 	Alexander Brevig
   || @contact alexanderbrevig@gmail.com
   || @contribution Adrian Brzezinski adrb@wp.pl, http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?action=viewprofile;username=vzhang
   || @contribution Orange Cat, https://github.com/Orange-Cat/MenuBackend
   ||
   || @description
   || | Provide an easy way of making menus
   ||
   || #
   || @license
   || | This library is free software; you can redistribute it and/or
   || | modify it under the terms of the GNU Lesser General Public
   || | License as published by the Free Software Foundation; version
   || | 2.1 of the License.
   || |
   || | This library is distributed in the hope that it will be useful,
   || | but WITHOUT ANY WARRANTY; without even the implied warranty of
   || | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   || | Lesser General Public License for more details.
   || |
   || | You should have received a copy of the GNU Lesser General Public
   || | License along with this library; if not, write to the Free Software
   || | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
   || #
   ||
 */

#ifndef MenuBackend_h
#define MenuBackend_h

#include <Arduino.h>
#include <String.h>

/*
   A menu item will be a container for an item that is a part of a menu
   Each such item has a logical position in the hierarchy as well as a text and maybe a mnemonic shortkey
 */
 
class MenuBackend;

class MenuItem {
  friend class MenuBackend;

  public:
    MenuItem(const char* itemName, char shortKey='\0' ) : name(itemName), shortkey(shortKey) {
      flash_name = NULL;
      before = right = after = left = 0;
    }
    MenuItem(const __FlashStringHelper* itemName, char shortKey='\0' ) : flash_name(itemName), shortkey(shortKey) {
      name = NULL;
      before = right = after = left = 0;
    }

    const char* getName() const { return name; }
    const __FlashStringHelper* getFlashName() const { return flash_name; }

    char getShortkey() const { return shortkey; }
    bool hasShortkey() const { return (shortkey!='\0'); }
    void setBack(MenuItem *b) { back = b; }
    void setBack(MenuItem &b) { back = &b; }
    void setLeft(MenuItem *l) { left = l; }
    void setLeft(MenuItem &l) { left = &l; }
    MenuItem* getBack() const { return back; }
    MenuItem* getBefore() const { return before; }
    MenuItem* getRight() const { return right; }
    MenuItem* getAfter() const { return after; }
    MenuItem* getLeft() const { return left; }

    MenuItem *moveBack() { return back; }

    MenuItem *moveUp() { 
      if (before) { before->back = this; }
      return before; 
    }

    MenuItem *moveDown() { 
      if (after) { after->back = this; }
      return after; 
    }

    MenuItem *moveLeft() { 
      if (left) { left->back = this; }
      return left; 
    }

    MenuItem *moveRight() { 
      if (right) { right->back = this; }
      return right; 
    }

    //default vertical menu
    MenuItem &add(MenuItem &mi) { return addAfter(mi); }

    MenuItem &addBefore(MenuItem &mi) {
      mi.after = this;
      before = &mi;
      if ( !mi.back ) mi.back = back;
      return mi;
    }
    MenuItem &addRight(MenuItem &mi) {
      mi.left = this;
      right = &mi;
      if ( !mi.back ) mi.back = back;
      return mi;
    }
    MenuItem &addAfter(MenuItem &mi) {
      mi.before = this;
      after = &mi;
      if ( !mi.left ) mi.left = left;
      if ( !mi.back ) mi.back = back;
      return mi;
    }
    MenuItem &addLeft(MenuItem &mi) {
      mi.right = this;
      left = &mi;
      if ( !mi.back ) mi.back = back;
      return mi;
    }

 public:
   bool operator==(const char* test) const {
    if (getName() != NULL)
       return String(getName()) == test;
    else
       return String(getFlashName()) == test;
   }

   bool operator==(const String& test) const {
    if (getName() != NULL)
       return String(getName()) == test;
    else
       return String(getFlashName()) == test;
   }

   bool operator==(const MenuItem &rhs) const {
    if (getName() != NULL) { 
      if (rhs.getName() != NULL)
       return String(getName()) == rhs.getName();
      else
       return String(getName()) == String(rhs.getFlashName());
    }
    else {
      if (rhs.getName() != NULL)
       return String(getFlashName()) == rhs.getName();
      else
       return String(getFlashName()) == String(rhs.getFlashName());
    }
   }

  protected:
    const char* name;
    const __FlashStringHelper* flash_name;
    const char shortkey;

    MenuItem *before;
    MenuItem *right;
    MenuItem *after;
    MenuItem *left;
    MenuItem *back;
};

struct MenuChangeEvent {
  const MenuItem &from;
  const MenuItem &to;
};

struct MenuUseEvent {
  const MenuItem &item;
};

typedef void (*cb_change)(MenuChangeEvent, void *context);
typedef void (*cb_use)(MenuUseEvent, void *context);
typedef MenuItem& MenuItemRef;

class MenuBackend {
  public:

    MenuBackend(cb_use menuUse, cb_change menuChange, void *context) : root("MenuRoot") {
      current = &root;
      root.left = &root;
      cb_menuChange = menuChange;
      cb_menuUse = menuUse;
      cb_context = context;
    }

    MenuItemRef getRoot() {
      return root;
    }
    MenuItemRef getCurrent() {
      return *current;
    }

    void moveBack() {
      setCurrent(current->getBack());
    }

    void moveUp() {
      setCurrent(current->moveUp());
    }

    void moveDown() {
      setCurrent(current->moveDown());
    }

    void moveLeft() {
      setCurrent(current->moveLeft());
    }

    void moveRight() {
      setCurrent(current->moveRight());
    }

    void use(char shortkey)
    {
      recursiveSearch(shortkey,&root);
      use();
    }

    void use() {
      //current->use();
      if (cb_menuUse) {
        MenuUseEvent mue = { *current };
        cb_menuUse(mue, cb_context);
      }
    }

    void toRoot() {
      setCurrent(&getRoot());
    }

  private:
    void setCurrent( MenuItem *next ) {
      if (next) {
        if (cb_menuChange) {
          MenuChangeEvent mce = { *current, *next };
          (*cb_menuChange)(mce, cb_context);
        }
        current = next;
      }
    }
    void foundShortkeyItem(MenuItem *mi) {
      mi->setBack(current);
      current = mi;
    }
    char canSearch(const char shortkey, MenuItem *m) {
      if (m==0) { return 0; }
      else  {
        if (m->getShortkey()==shortkey) {
          foundShortkeyItem(m);
          return 1;
        }
        return -1;
      }
    }
    void rSAfter(const char shortkey, MenuItem *m) {
      if (canSearch(shortkey,m)!=1) {
        rSAfter(shortkey, m->getAfter());
        rSRight(shortkey, m->getRight());
        rSLeft(shortkey, m->getLeft());
      }
    }
    void rSRight(const char shortkey, MenuItem *m) {
      if (canSearch(shortkey,m)!=1) {
        rSAfter(shortkey, m->getAfter());
        rSRight(shortkey, m->getRight());
        rSBefore(shortkey, m->getBefore());
      }
    }
    void rSLeft(const char shortkey, MenuItem *m) {
      if (canSearch(shortkey,m)!=1) {
        rSAfter(shortkey, m->getAfter());
        rSLeft(shortkey, m->getLeft());
        rSBefore(shortkey, m->getBefore());
      }
    }
    void rSBefore(const char shortkey, MenuItem *m) {
      if (canSearch(shortkey,m)!=1) {
        rSRight(shortkey, m->getRight());
        rSLeft(shortkey, m->getLeft());
        rSBefore(shortkey, m->getBefore());
      }
    }
    void recursiveSearch(const char shortkey, MenuItem *m) {
      if (canSearch(shortkey,m)!=1) {
        rSAfter(shortkey, m->getAfter());
        rSRight(shortkey, m->getRight());
        rSLeft(shortkey, m->getLeft());
        rSBefore(shortkey, m->getBefore());
      }
    }

    MenuItem root;
    MenuItem *current;

    cb_change cb_menuChange;
    cb_use cb_menuUse;

    void *cb_context;
};

#endif

