heap
====

Heap (priority queue) data structure with random access and priority modification.

This is basically a key-value container with the added functionality of getting (or removing) the element with the min. value in O(1) time.

template<typename key, typename value,
         typename less_type = std::less<value> >
class heap;

Constructor
-----------

heap()
Constructs heap.


Modifiers
---------

void insert(const key &k, elem e)
Inserts item k with value e.
Inserting an already inserted key results in assertion failure.

void update(const key &k, value new_val)
Changes value of item k. Inserts if k isn't present.

void erase(const key &k)
Removes item k. Doesn't do anything if k is not present.

void pop_min()
Removes item with smallest value.
Assertion failure if heap is empty.


Accessors
--------

std::pair<key, value> get_min() const
Get element with min. value.

const value& operator[](const key &k) const
Get value of element k.
Note that you can't modify the value through this.


Capacity
--------

bool empty() const
size_type size() const

