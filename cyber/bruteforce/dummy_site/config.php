<?php
   define('DB_SERVER', 'localhost');
   define('DB_USERNAME', '<db user>');
   define('DB_PASSWORD', '<db user password>');
   define('DB_DATABASE', '<db name>');
   $db = mysqli_connect(DB_SERVER,DB_USERNAME,DB_PASSWORD,DB_DATABASE);
?>
