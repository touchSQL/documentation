
<!-- POST DATA -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
$(document).ready(function() {
    $("#submit").click(function() {
        var name = $("#name").val(); 
        var lname = $("#lname").val(); 
            $.ajax({
                type: "POST",
                url: "php-integration-post-data.php",
                data: {
                    name: name,
                    lname: lname
                },
                cache: false,
                success: function(data) {
                    $('#data').html(data); 
                },
            });
    });
});

<div id="data"></div>
<form>
<input type="text" id="name" name="name" value="Gopal">
<input type="text" id="lname" name="lname" value="Dubey">
<input type="button" value="Submit" id="submit">
</form>