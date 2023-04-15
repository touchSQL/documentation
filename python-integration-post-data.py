## POST DATA
import urllib.request    
import json
import pandas as pd
import re

query_c = "insert into `test` (`name`,`lname`) values ('Gopal','Dubey')"
query = re.sub(r"\s", "+", query_c)
my_request = urllib.request.urlopen("https://touchsql.com/api-in.php?database=myDB&api=Your_API&key=Your_Key&query="+query)

my_HTML = my_request.read().decode("utf8")
# a dictionary
data = json.loads(my_HTML)
print(data)