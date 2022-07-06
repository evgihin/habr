import requests
import json
import time

proxys = [ '1.1.1.1', '2.2.2.2', '3.3.3.3' ]
keys = [ '3b4qx4nu7KI9BiSnNFOeYsN7sVybkd4H', '3b4qx4nu7KI9BiSnNFOeYsN7sVybkd4H', '3b4qx4nu7KI9BiSnNFOeYsN7sVybkd4H' ]
head = 'http://ipqualityscore.com/api/json/ip/'
tail = '?strictness=1&allow_public_access_points=false&fast=false&lighter_penalties=true&mobile=trues'
i = 0
bad_proxy = []

for p in proxys:
	r = requests.get(head + keys[i] + '/' + p + tail)
	val = r.json()
	if val['fraud_score'] <= 100:
		i += 1	
		bad_proxy.append(p)
print(bad_proxy)
