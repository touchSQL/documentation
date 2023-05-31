<?php 
// POST DATA 
if(isset($_POST["submit"])){
$name = $_POST["name"];
$lname = $_POST["lname"];
$query_c = "INSERT INTO `test`(`name`,`lname`) VALUES ('$name','$lname')";
$query = preg_replace("/ /i", "+", $query_c);

// If you use query encryption, you will need to use the following URL: "https://post.touchsql.com/v2/?database=mydb&api=Your_API&key=Your_Key&query=$query".

$url = "https://post.touchsql.com/?database=mydb&api=Your_API&key=Your_Key&query=$query";  // Use can also use file_get_contents(); method
$ch = curl_init();   // Use can also use file_get_contents(); method
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_URL, $url);
$exec = curl_exec($ch);
$data = json_decode($exec, true);
echo "<pre>";
print_r($data);
echo "</pre>";

if($data["TRUE"] == "TRUE")
{
    echo "Data inserted";
}
elseif($data["FALSE"] == "FALSE"){
    echo "Try again";
}
}
?>
<form method="post">
    <input type="text" name="name" placeholder="FIRST NAME">
    <input type="text" name="lname" placeholder="LAST NAME">
    <input type="submit" name="submit" value="Insert">
</form>
