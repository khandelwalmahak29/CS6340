#!/usr/bin/env python

import os
import sys
import time
from glob import glob

from Topology import *
from helpers import *
from tests_validator_lib import validateStudentOutput

script_dir = sys.path[0]
topology_dir = script_dir + '/tests/topologies'
solution_dir = script_dir + '/tests/solutions'
output_dir   = script_dir + '/tests/outputs'

# test that needed directories are present
if not (os.path.isdir(topology_dir) and os.path.isdir(solution_dir)):
    print "Directories test_topologies and test_solutions don't exist"
    exit()
# if output_dir is present, empty it, else create it
if os.path.isdir(output_dir):
    for f in os.listdir(output_dir):
        os.remove(output_dir + '/' + f)
else:
    os.mkdir(output_dir)

#
# run the topologies
#
# measure execution time for entire run
tests_time_start = time.time()

for topology_file in sorted(os.listdir(topology_dir), key=str.lower):
    topology_name = os.path.splitext(topology_file)[0]
    input_file = topology_dir + '/' + topology_file
    output_file = output_dir + '/' + topology_name + '.log'
    solution_file = solution_dir + '/' + topology_name + '.log'

    open_log(output_file)
    topo = Topology(input_file)

    # measure execution time of this topo
    topo_time_start = time.time()

    topo.run_topo()
    finish_log()

    topo_time_end = time.time()
    topo_time_total = topo_time_end - topo_time_start
    print "executed : {} in {}s".format(topology_name, topo_time_total)

tests_time_end = time.time()
tests_time_total = tests_time_end - tests_time_start


# check the results
for output_file in sorted(os.listdir(output_dir), key=str.lower):
    topology_name = os.path.splitext(output_file)[0]
    output_file   = output_dir   + '/' + topology_name  +  '.log'
    solution_file = solution_dir + '/' + topology_name  +  '.log'

    with open(output_file, "r") as f:
        output_log_str = f.read()

    with open(solution_file, "r") as f:
        correct_log_str = f.read().strip()

    iterations = output_log_str.split("-----")
    final_log_str = iterations[-2].strip()
    #print "found {:^5} iterations: in {}".format(len(iterations) - 1, output_file)
    iteration_str = "  <<< {:>4} iterations: in {}".format(len(iterations) - 1, output_file)
    validateStudentOutput(output_file)
    c = sorted(correct_log_str.split("\n"))
    m = sorted(final_log_str.split("\n"))

    lines_compliance = []
    for cl, ml in zip(c, m):
        c_items_str = ",".join(sorted(cl.split(":")[-1].split(",")))
        m_items_str = ",".join(sorted(ml.split(":")[-1].split(",")))
        lines_compliance.append(c_items_str == m_items_str)
        lines_compliance.append(cl.split(":")[0] == ml.split(":")[0])
    #print 'Topo Name: ' + topology_name
    if all(lines_compliance) and len(c) == len(m):
        print "   PASSED" + iteration_str
    else:
        print "** ERROR " + iteration_str

print 'All tests ran in {}s'.format(tests_time_total)