#ifndef TrackDATA_H
#define TrackDATA_H

// Track reconstructed from clusters in the inner tracker
// author: C. Bernet, B. Hegner



namespace fcc {
class TrackData {
public:
  float Chi2;  ///< chi2 returned by the track fit
  unsigned Ndf;  ///< Number of degrees of freedom of the track fit
  unsigned Bits;  ///< Stores flags
};
} // namespace fcc

#endif
