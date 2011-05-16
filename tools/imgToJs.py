#!/usr/bin/env python

import csv
import codecs
from collections import defaultdict
import jsonlib

def loadImg(filename):
    data = defaultdict(dict)
    
    with codecs.open(filename, 'r+b', "utf-8") as fp:
        reader = csv.reader(fp, delimiter=",", quotechar='"')
        
        for row in reader:
            if not 'items' in data[row[0]]:
                data[row[0]]['items'] = {}
                
            data[row[0]]['items'][row[7]] = [int(row[1]), int(row[2]), int(row[3]), int(row[4]), int(row[5]), int(row[6])]
            
            
    return data
            

if __name__ == '__main__':
    import sys
    
    if len(sys.argv) != 3:
        print "Usage: %s <from-img> <to-json>" % sys.argv[0]
        exit(1)
    
    with open(sys.argv[2], 'w+b') as fp:
        data = jsonlib.dumps(loadImg(sys.argv[1]), encoding="utf-8")
        fp.write(data)
