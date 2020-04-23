import sys
import os
from multiprocessing import Pool

def GenerateConfigFile(outname, in_name, gamma_e):
	"""
	Generates a config file from a template
	"""

	outfile = open(outname, "w")
	template_file = open(in_name, "r")
	template = template_file.readlines()
	template_file.close()

	for line in template:
		if "gammaEnergy:" in line:
			line = "gammaEnergy:\t%d\n" % gamma_e 
		outfile.write(line)
	outfile.close()

def RunMiniballTREX(energy, number_of_gammas, template):

	# First we generate a folder to store the input and result
	work_folder = "Eg_%d" % energy
	res_file = work_folder + "/Eg%d.root" % (int(energy))
	conf_file = work_folder + "/config.dat"
	log_file = work_folder + "/log.txt"
	if not os.path.exists(work_folder):
		os.system("mkdir %s" % work_folder)

	GenerateConfigFile(conf_file, template, energy)
	os.system("./MiniballTRex -f %s -s %s -n %d > %s" % (res_file, conf_file, number_of_gammas, log_file))


if __name__ == '__main__':
	num_events = 1000
	if len(sys.argv) == 2:
		try:
			num_events = int(sys.argv[1])
		except:
			print("Unable to understand number of events, try again.")
			exit(-1)

	energies = [100]
	for val in range(200, 10100, 200):
		energies.append(val)
	def Run(e):
		RunMiniballTREX(e, num_events, "GammaSource_Efficency_66Ni_dp.dat")
	print("Running MiniballREX with %s with %s processes" % (num_events, os.cpu_count()))
	p = Pool(os.cpu_count())
	p.map(Run, energies)