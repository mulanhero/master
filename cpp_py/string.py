import re

def sub_str():
	str_orig = "hello, world!"
	o_str = str_orig[4]
	llo_str = str_orig[2:5]
	print(o_str)
	print(llo_str)

def find_str():
	str_orig = "hello, world!"
	to_find = "wo"
	index = str_orig.find(to_find, 5)
	if index != -1:
		print("find '" + to_find + "' in '" + str_orig + " at index:" + str(index))
	else:
		print("not found")

def concat():
	first = "hello,"
	second = "world!"
	result = first + " " + second
	print("concat:" + result)

def replace():
	str_orig = "hello, world!"
	to_replace = "hello"
	result = ""
	if to_replace in str_orig:
		result = str_orig.replace(to_replace, "hi")	
	print(str_orig)
	print(result)
		
def to_string_to_float():
	pi = 3.1415
	pi_str = str(pi)
	print(pi_str)
	
	pi_f = float(pi_str)
	print("area with 2-diameter: %f" % (pi_f*2*2))

def str_len():
	str_orig = "hello, world!"
	size = len(str_orig)
	print(size)

def str_split():
	str_orig = "123,456,789"
	items = str_orig.split(',')
	result = 0
	for item in items:
		result += int(item);
	print("result:" + str(result))

def str_compare():
	str1 = "hello, world!"
	if str1 == "hello, world!":
		print("==")

def str_reverse():
	str = "12345"
	result = "".join(reversed(str))
	print("after reverse, result:" + result)

def str_join():
	str_list = ["123", "456", "789"]
	result = ",".join(str_list)
	print("result:" + result)

def node_parser_with_split():
	str_orig = "node[13-15].sth.com"
	results = []
	items = re.split('\[|-|\]', str_orig) 
	start = int(items[1])
	end = int(items[2])
	while (start <= end):
		tmp = items[0] + str(start) + items[3]
		start = start + 1
		results.append(tmp)
	for item in results:
		print(item")
		
if __name__ == '__main__':
	sub_str()
	find_str()
	concat()
	replace()
	to_string_to_float()
	str_len()
	str_split()
	str_compare()
	str_reverse()
	str_join()
	node_parser_with_split()
