// standard includes
#include <stdexcept>


#include "TrackClusterCollection.h"

namespace fcc {

TrackClusterCollection::TrackClusterCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new TrackClusterDataContainer() ) {
  
}

TrackClusterCollection::~TrackClusterCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
};

const TrackCluster TrackClusterCollection::operator[](unsigned int index) const {
  return TrackCluster(m_entries[index]);
}

const TrackCluster TrackClusterCollection::at(unsigned int index) const {
  return TrackCluster(m_entries.at(index));
}

int  TrackClusterCollection::size() const {
  return m_entries.size();
}

TrackCluster TrackClusterCollection::create(){
  auto obj = new TrackClusterObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return TrackCluster(obj);
}

void TrackClusterCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TrackClusterCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void TrackClusterCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TrackClusterObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool TrackClusterCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void TrackClusterCollection::push_back(ConstTrackCluster object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void TrackClusterCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<TrackClusterDataContainer*>(address);
}


const TrackCluster TrackClusterCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const TrackCluster* TrackClusterCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const TrackClusterCollectionIterator& TrackClusterCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
