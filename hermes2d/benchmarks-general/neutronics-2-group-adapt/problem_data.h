#include "hermes2d.h"

using namespace WeakFormsNeutronics::Multigroup::MaterialProperties::Diffusion;

//////  Physical parameters.  /////////////////////////////////////////////////////////////////

const std::string mesh_file = "square.mesh";

const std::string regions[4] = {
  "region1", "region2", "region3", "region4"
};

// Two-group material properties for the 4 macro regions.

/*
const MaterialPropertyMap1 D = material_property_map<rank1>
(
  regions[0], row(1.12)(0.6)
)(
  regions[1], row(1.2)(0.5)
)(
  regions[2], row(1.35)(0.8)
)(
  regions[3], row(1.3)(0.9)
);
*/
// FIXME: The benchmark and its exact solution must be fixed for discontinuous D

const MaterialPropertyMap1 D = material_property_map<rank1>
(
  regions[0], row(1)(0.5)
)(
  regions[1], row(1)(0.5)
)(
  regions[2], row(1)(0.5)
)(
  regions[3], row(1)(0.5)
);

const MaterialPropertyMap1 Sr = material_property_map<rank1>
(
  regions[0], row(0.011)(0.13)
)(
  regions[1], row(0.09)(0.15)
)(
  regions[2], row(0.035)(0.25)
)(
  regions[3], row(0.04)(0.35)
);

const MaterialPropertyMap1 nSf = material_property_map<rank1>
(
  regions[0], row(0.0025)(0.15)
)(
  regions[1], row(0.00)(0.00)
)(
  regions[2], row(0.0011)(0.1)
)(
  regions[3], row(0.004)(0.25)
);

const double nu = 2.43;

const double chi_data[2] = {1, 0};
const rank1 chi(chi_data, chi_data+2);

const MaterialPropertyMap2 Ss = material_property_map<rank2>
(
  regions[0],
  matrix
  (
    row(0.0)(0.0)
  )(
    row(0.05)(0.0)
  )
)(
  regions[1],
  matrix
  (
    row(0.0)(0.0)
  )(
    row(0.08)(0.0)
  )
)(
  regions[2],
  matrix
  (
    row(0.0)(0.0)
  )(
    row(0.025)(0.0)
  )
)(
  regions[3],
  matrix
  (
    row(0.0)(0.0)
  )(
    row(0.014)(0.0)
  )
);
