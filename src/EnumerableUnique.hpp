#pragma once

class EnumerableUnique {
  static uint64_t id_global;

 protected:
  const uint64_t uid;
  EnumerableUnique() : uid(EnumerableUnique::id_global++){};
};
uint64_t EnumerableUnique::id_global = 0;