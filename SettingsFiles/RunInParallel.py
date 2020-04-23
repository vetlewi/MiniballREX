import os
from multiprocessing import Pool

def GenerateConfigFile(outname, template, gamma_e):
	"""
	Generates a config file from a template
	"""

	outfile = open(outname, "w")
	template_file = open(input_name, "r")
	template = template_file.readlines()
	template_file.close()

	for line in template:
		if "gammaEnergy:" in line:
			line = "gammaEnergy:\t%d\n" % gamma_e 
		outfile.write(line)
	outfile.close()

def RunMiniballTREX(energy, number_of_gammas, template):

	# First we generate a folder to store the input and result
	work_folder = "Eg_%f" % energy
	res_file = work_folder + "Eg%d" % (int(energy))
	conf_file = work_folder + "/config.dat"
	os.system("mkdir %s" % work_folder)

	GenerateConfigFile(conf_file, template, energy)
	os.system("./MiniballTRex -f %s -s %s -n %d" % (res_file, conf_file, number_of_gammas))


if __name__ == '__main__':
	energies = [100]
	for val in range(200, 10100, 200):
		energies.append(val)
	def Run(e):
		RunMiniballTREX(e, 1000, "GammaSource_Efficency_66Ni_dp.dat")
	p = Pool(28)
	p.map(Run, energies)