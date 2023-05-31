## GET DATA
import urllib.request    
import json
import pandas as pd
import re

query_c = "SELECT * FROM `test`"
query = re.sub(r"\s", "+", query_c)

# If you use query encryption, you will need to use the following URL: "https://get.touchsql.com/v2/?database=mydb&api=Your_API&key=Your_Key&query=query".

my_request = urllib.request.urlopen("https://get.touchsql.com/?database=myDB&api=Your_API&key=Your_Key&query="+query)

my_HTML = my_request.read().decode("utf8")
# a dictionary
data = json.loads(my_HTML)
print(pd.DataFrame(data).T)

## OUTPUT
##id    name  lname
##1  1   Gopal  Dubey
##2  2  Anjali  Dubey
##3  3  Rajesh  Dubey
##4  4   Kanti  Dubey
