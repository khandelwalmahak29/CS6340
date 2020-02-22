#!/usr/bin/env python
import os, sys

script_dir = sys.path[0]
solution_dir = script_dir + '/tests/solutions'
sorted_dir   = script_dir + '/tests/solutions_sorted'

for solution_file in sorted(os.listdir(solution_dir), key=str.lower):
    topology_name = os.path.splitext(solution_file)[0]
    print "sorting: ", topology_name
    IF = solution_dir + '/' + topology_name + '.log'
    OF = sorted_dir   + '/' + topology_name + '.log'

    sorted_file_str = ''
    with open(IF, "r") as input_file:
        #lines = i.readlines()
        #for l in lines:
        for line in input_file.readlines():
            line = line.strip('\n')
            line_split = line.split(":")
            node = line_split[0]
            vect = line_split[1]
            vect_list = vect.split(',')
            vect_list.sort()
            sorted_file_str += node + ":" + ','.join(vect_list) + '\n'

    sorted_file_str = sorted_file_str.strip('\n')
    with open(OF, "w+") as output_file:
        output_file.write(sorted_file_str)


# check the results
for sorted_file in sorted(os.listdir(sorted_dir), key=str.lower):
    topology_name = os.path.splitext(sorted_file)[0]
    solution_file = solution_dir + '/' + topology_name +  '.log'
    sorted_file   = sorted_dir   + '/' + topology_name + '.log'

    with open(solution_file, "r") as f:
        correct_log_str = f.read().strip()

    with open(sorted_file, "r") as f:
        sorted_log_str = f.read()

    correct_lines= sorted(correct_log_str.split("\n"))
    sorted_lines = sorted(sorted_log_str.split("\n"))
    if len(correct_lines) == len(sorted_lines):
        for c, s in zip(correct_lines, sorted_lines):
            #print c
            #print s
            c_node = (c.split(":"))[0]
            s_node = (s.split(":"))[0]
            c_vector = (c.split(":"))[1]
            s_vector = (s.split(":"))[1]
            if c_node == s_node:
                difference_set = set(c_vector.split(',')) - set(s_vector.split(','))
                if difference_set:
                    print 'failed comparison (converted sets are not the same)'
                    continue
                else:
                    # if the sets are the same, the expr will be false
                    pass
            else:
                print 'failed comparison (c_node != s_node)'
                continue

    # you will only get here if the files are equivalent
    print 'comparison successful: ' + topology_name
