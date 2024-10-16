#include "ParticleSys.h"

void ParticleSys::fuente()
{

	//myPops.push_back(new Particle(p, v, a, 0.01, 1));

	const int nrolls = 10000;  // number of experiments
	const int nstars = 100;    // maximum number of stars to distribute

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(5.0, 2.0);

	int pa[10] = {};

	for (int i = 0; i < nrolls; ++i) {
		double number = distribution(generator);
		if ((number >= 0.0) && (number < 10.0)) ++pa[int(number)];
	}

	std::cout << "normal_distribution (5.0,2.0):" << std::endl;

	for (int i = 0; i < 10; ++i) {
		std::cout << i << "-" << (i + 1) << ": ";
		std::cout << std::string(pa[i] * nstars / nrolls, '*') << std::endl;
	}

}
