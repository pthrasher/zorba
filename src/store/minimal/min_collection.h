#ifndef ZORBA_STORE_MINIMAL_COLLECTION
#define ZORBA_STORE_MINIMAL_COLLECTION

#include <set>
#include "common/common.h"

#include "store/api/iterator.h"
#include "store/api/collection.h"
#include "store/util/latch.h"

namespace zorba { 
  namespace store {

/*******************************************************************************

********************************************************************************/
class SimpleCollection : public Collection
{
  friend class CollectionIter;

public:
  class CollectionIter : public Iterator
	{
  private:
    SimpleCollection_t            theCollection;
    SYNC_CODE(AutoLatch                     theLatch;)
    std::set<Item_t>::iterator    theIterator;

  public:
    CollectionIter(SimpleCollection* collection);

    virtual ~CollectionIter() { }

    void open();
    Item_t next();
    void reset();
    void close();
  };


protected:
  Item_t               theUri;
  std::set<Item_t>     theXmlTrees;
  SYNC_CODE(Latch                theLatch;)

public:
  SimpleCollection(Item* uri);
  virtual ~SimpleCollection();

  Item_t getUri() { return theUri; }

  ulong size() const { return theXmlTrees.size(); }

  Iterator_t getIterator(bool idsNeeded);

  Item_t addToCollection(std::istream& stream);
  void addToCollection(const Item* node);
  void addToCollection(Iterator* nodes);

  void removeFromCollection(const Item* node);  
};

} // namespace store
} // namespace zorba

#endif
