// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

#include "cls/journal/cls_journal_types.h"
#include "common/Formatter.h"

namespace cls {
namespace journal {

void EntryPosition::encode(bufferlist& bl) const {
  ENCODE_START(1, 1, bl);
  ::encode(tag, bl);
  ::encode(tid, bl);
  ENCODE_FINISH(bl);
}

void EntryPosition::decode(bufferlist::iterator& iter) {
  DECODE_START(1, iter);
  ::decode(tag, iter);
  ::decode(tid, iter);
  DECODE_FINISH(iter);
}

void EntryPosition::dump(Formatter *f) {
  f->dump_string("tag", tag);
  f->dump_unsigned("tid", tid);
}

void EntryPosition::generate_test_instances(std::list<EntryPosition *> &o) {
  o.push_back(new EntryPosition());
  o.push_back(new EntryPosition("id", 2));
}

void ObjectSetPosition::encode(bufferlist& bl) const {
  ENCODE_START(1, 1, bl);
  ::encode(object_number, bl);
  ::encode(entry_positions, bl);
  ENCODE_FINISH(bl);
}

void ObjectSetPosition::decode(bufferlist::iterator& iter) {
  DECODE_START(1, iter);
  ::decode(object_number, iter);
  ::decode(entry_positions, iter);
  DECODE_FINISH(iter);
}

void ObjectSetPosition::dump(Formatter *f) {
  f->dump_unsigned("object_number", object_number);
  f->open_array_section("entry_positions");
  for (size_t i = 0; i < entry_positions.size(); ++i) {
    f->open_object_section("entry_position");
    entry_positions[i].dump(f);
    f->close_section();
  }
  f->close_section();
}

void ObjectSetPosition::generate_test_instances(
    std::list<ObjectSetPosition *> &o) {
  o.push_back(new ObjectSetPosition());

  EntryPositions entry_positions;
  entry_positions.push_back(EntryPosition("tag1", 120));
  entry_positions.push_back(EntryPosition("tag2", 121));
  o.push_back(new ObjectSetPosition(1, entry_positions));
}

void Client::encode(bufferlist& bl) const {
  ENCODE_START(1, 1, bl);
  ::encode(id, bl);
  ::encode(description, bl);
  ::encode(commit_position, bl);
  ENCODE_FINISH(bl);
}

void Client::decode(bufferlist::iterator& iter) {
  DECODE_START(1, iter);
  ::decode(id, iter);
  ::decode(description, iter);
  ::decode(commit_position, iter);
  DECODE_FINISH(iter);
}

void Client::dump(Formatter *f) {
  f->dump_string("id", id);
  f->dump_string("description", description);
  f->open_object_section("commit_position");
  commit_position.dump(f);
  f->close_section();
}

void Client::generate_test_instances(std::list<Client *> &o) {
  o.push_back(new Client());
  o.push_back(new Client("id", "desc"));

  EntryPositions entry_positions;
  entry_positions.push_back(EntryPosition("tag1", 120));
  entry_positions.push_back(EntryPosition("tag1", 121));
  o.push_back(new Client("id", "desc", ObjectSetPosition(1, entry_positions)));
}

} // namespace journal
} // namespace cls
