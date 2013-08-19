#ifndef __HEAP_HPP__
#define __HEAP_HPP__

#include <cassert>
#include <vector>
#include <utility>
#include <boost/unordered_map.hpp>

#define PARENT(x) (((x)-1)/2)
#define LEFT_CHILD(x) (((x)*2)+1)
#define RIGHT_CHILD(x) (((x)*2)+2)

// min-heap
template<typename key, typename value,
         typename less_type = std::less<value> >
class heap {
 public:
  typedef typename std::vector<
    std::pair<value, void*> >::size_type size_type;

  heap() {}
  inline bool empty() const {
    return data_.empty();
  }
  inline size_type size() const {
    return data_.size();
  }
  void insert(const key &k, value e) {
    assert(locs_.find(k) == locs_.end());

    index_type index = data_.size();
    loc_type *loc = new loc_type(k, index);
    data_.push_back(make_pair(e, loc));
    locs_[k] = &loc->second;

    bubble_up(index);
  }
  void update(const key &k, value new_val) {
    if (locs_.find(k) == locs_.end()) {
      insert(k, new_val);
    } else {
      index_type index = *reinterpret_cast<index_type*>(locs_.find(k)->second);
      value old_val = data_[index].first;
      data_[index].first = new_val;
      if (less_(old_val, new_val)) {
        bubble_down(index);
      } else {
        bubble_up(index);
      }
    }
  }
  void erase(const key &k) {
    if (locs_.find(k) != locs_.end()) {
      index_type index = *locs_[k];
      swap_(index, data_.size() - 1);
      loc_type *loc = data_.back().second;
      locs_.erase(loc->first);
      delete loc;
      data_.pop_back();

      bubble_down(index);
    }
  }
  std::pair<key, value> get_min() const {
    if (!data_.empty())
      return make_pair(data_[0].second->first, data_[0].first);
    else
      return make_pair(key(), value());
  }
  void pop_min() {
    assert(!data_.empty());
    swap_(0, data_.size() - 1);
    loc_type *loc = data_.back().second;

    locs_.erase(loc->first);
    delete loc;
    data_.pop_back();

    bubble_down(0);
  }
  inline const value& operator[](const key &k) const {
    assert(locs_.find(k) != locs_.end());
    return data_[*locs_[k]].first;
  }

 private:
  typedef size_type index_type;
  typedef std::pair<key, index_type> loc_type;
  typedef boost::unordered_map<key, void*> map_type;

  inline void swap_(index_type a, index_type b) {
    std::pair<value, loc_type*> tmp = data_[a];
    data_[a] = data_[b];
    data_[b] = tmp;
    data_[a].second->second = a;
    data_[b].second->second = b;
  }
  inline void bubble_up(index_type index) {
    for (index_type p = PARENT(index); index > 0; p = PARENT(index)) {
      if (!less_(data_[p].first, data_[index].first)) {
        swap_(p, index);
        index = p;
      } else {
        break;
      }
    }
  }
  inline void bubble_down(index_type index) {
    while (true) {
      index_type l = LEFT_CHILD(index);
      index_type r = RIGHT_CHILD(index);
      if (r < data_.size() &&
          (!less_(data_[index].first, data_[l].first) ||
           !less_(data_[index].first, data_[r].first))) {
        if (less_(data_[l].first, data_[r].first)) {
          swap_(index, l);
          index = l;
          continue;
        } else {
          swap_(index, r);
          index = r;
          continue;
        }
      } else if (l < data_.size() &&
                 !less_(data_[index].first, data_[l].first)) {
        swap_(index, l);
        index = l;
        break;
      } else {
        break;
      }
    }
  }
  typedef std::vector<
    std::pair<value, loc_type*> > heap_vector_type;

  heap_vector_type data_;
  map_type locs_;
  less_type less_;
};

#undef PARENT
#undef LEFT_CHILD
#undef RIGHT_CHILD
#endif
