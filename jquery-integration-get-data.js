<!-- GET DATA -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
$(document).ready(function() {
    $("#submit").click(function() {
        var name = $("#name").val(); 
            $.ajax({
                type: "POST",
                url: "php-integration-get-data.php",
                data: {
                    name: name
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
<input type="button" value="Submit" id="submit">
</form>