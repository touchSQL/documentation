## GET DATA
import urllib.request    
import json
import pandas as pd
import re

query_c = "SELECT * FROM `test`"
query = re.sub(r"\s", "+", query_c)
my_request = urllib.request.urlopen("https://apiout.touchsql.com/?database=myDB&api=Your_API&key=Your_Key&query="+query)

my_HTML = my_request.read().decode("utf8")
# a dictionary
data = json.loads(my_HTML)
print(pd.DataFrame(data).T)
