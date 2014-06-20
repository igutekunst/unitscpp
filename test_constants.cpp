// Program to test various defined physical constants when the -s
// option is used with the gen.py script.

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
using namespace std;

#include "test_constants.h"

// The following definitions of units were gotten from
// http://physics.nist.gov/cuu/Constants/Table/allascii.txt.  These
// numbers are intended to be as independent as possible from the
// numbers I put into the script.

const Mass alpha_particle_mass = 6.64465620e-27*kg;
const Mass atomic_mass_constant = 1.660538782e-27*kg;
const Charge atomic_unit_of_charge = 1.602176487e-19*C;
const Avogadro Avogadro_constant = 6.02214179e23/mol;
const MagneticMoment Bohr_magneton = 927.400915e-26*J/T;
const Entropy Boltzmann_constant = 1.3806504e-23*J/K;
const Permittivity electric_constant = 8.854187817e-12*F/m;
const Permeability magnetic_constant = 12.566370614e-7*N/(A*A);
const ChargeToMass electron_charge_to_mass_quotient = 1.758820150e11*C/kg;
const Mass electron_mass = 9.10938215e-31*kg;
const NT electron_proton_mass_ratio = 5.4461702177e-4;
const Energy electron_volt = 1.602176487e-19*J;
const Charge elementary_charge = 1.602176487e-19*C;
const ElectrochemicalConstant Faraday_constant = 96485.3399*C/mol;
const GasConstant molar_gas_constant = 8.314472*J/(mol*K);
const NT neutron_electron_mass_ratio = 1838.6836605;
const Mass neutron_mass = 1.674927211e-27*kg;
const GravitationalConstant Newtonian_constant_of_gravitation = 6.67428e-11*m3/(kg*s*s);
const Action Planck_constant = 6.62606896e-34*J*s;
const ChargeToMass proton_charge_to_mass_quotient = 9.57883392e7*C/kg;
const Mass proton_mass = 1.672621637e-27*kg;
const WaveNumber Rydberg_constant = 10973731.568527/m;
const Velocity speed_of_light_in_vacuum = 299792458*m/s;
const Acceleration standard_acceleration_of_gravity = 9.80665*m/(s*s);
const Pressure standard_atmosphere = 101325*Pa;
const StefanBoltzmannLaw Stefan_Boltzmann_constant = 5.670400e-8*W/(m*m*K*K*K*K);

template<typename T>
bool chk(const T & a, const T & b, const NT & eps)
{
    T diff(a-b);
    return fabs(diff())/fabs(a()) <= eps;
}

template<typename T>
bool chk(const NT & a, const T & b, const NT & eps)
{
    T diff(a-b());
    return fabs(diff())/fabs(a) <= eps;
}

int main(void)
{
    cout << setprecision(15);
    NT eps = 1e-6;

    assert(chk(alpha_particle_mass, AlphaParticleMass, eps));
    assert(chk(atomic_mass_constant, amu, eps));
    assert(chk(atomic_unit_of_charge, ElectronCharge, eps));
    assert(chk(Avogadro_constant, AvogadroNumber, eps));
    assert(chk(Bohr_magneton, BohrMagneton, eps));
    assert(chk(Boltzmann_constant, BoltzmannConstant, eps));
    assert(chk(electric_constant, PermittivityOfVacuum, eps));
    assert(chk(magnetic_constant, PermeabilityOfVacuum, eps));
    assert(chk(electron_charge_to_mass_quotient, ElectronCharge/ElectronMass, eps));
    assert(chk(electron_mass, ElectronMass, eps));
    assert(chk(electron_proton_mass_ratio,  ElectronMass/ProtonMass, eps));
    assert(chk(electron_volt, eV, eps));
    assert(chk(elementary_charge, ElectronCharge, eps));
    assert(chk(Faraday_constant, FaradayConstant, eps));
    assert(chk(molar_gas_constant, MolarGasConstant, eps));
    assert(chk(neutron_mass, NeutronMass, eps));
    assert(chk(Newtonian_constant_of_gravitation, GravitationConstant, eps));
    assert(chk(Planck_constant, PlanckConstant, eps));
    assert(chk(proton_charge_to_mass_quotient, (ElectronCharge)/(ProtonMass), eps));
    assert(chk(proton_mass, ProtonMass, eps));
    assert(chk(speed_of_light_in_vacuum, SpeedOfLight, eps));
    assert(chk(standard_acceleration_of_gravity, AccelerationOfGravity, eps));
    assert(chk(standard_atmosphere, atm, eps));
    assert(chk(Stefan_Boltzmann_constant, StefanBoltzmannConstant, eps));
    assert(chk(neutron_electron_mass_ratio, NeutronMass/ElectronMass, eps));
    cout << __FILE__ << ":  tests passed" << endl;
    return 0;
}
