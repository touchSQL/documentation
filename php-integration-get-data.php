<?php 
// GET DATA 
if(isset($_POST["submit"])){
$name = $_POST["name"];
$query_c = "SELECT * FROM `test` where name like '$name'";
$query = preg_replace("/ /i", "+", $query_c);

// If you use query encryption, you will need to use the following URL: "https://get.touchsql.com/v2/?database=mydb&api=Your_API&key=Your_Key&query=$query".

$url = "https://get.touchsql.com/?database=mydb&api=Your_API&key=Your_Key&query=$query"; // Use can also use file_get_contents(); method
$ch = curl_init();   // Use can also use file_get_contents(); method
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_URL, $url);
$exec = curl_exec($ch);
echo "<pre>";
$data = json_decode($exec, true);
print_r($data); // print_r($data[1]["id"]);
echo "</pre>";
}
?>
<form method="post">
    <input type="text" name="name" placeholder="FIRST NAME">
    <input type="submit" name="submit" value="search">
</form>
