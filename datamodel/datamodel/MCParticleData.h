#ifndef MCParticleDATA_H
#define MCParticleDATA_H

// Monte-Carlo Particle, either generated or simulated.
// author: C. Bernet, B. Hegner

#include "BareParticle.h"

namespace fcc {
class MCParticleData {
public:
  fcc::BareParticle Core;  ///< Basic particle information.
};
} // namespace fcc

#endif
