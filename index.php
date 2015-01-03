<html>
<head>
</head>

<body style="background: #eea;">
<h1>Raspberry Server</h1>
<p>Starten bzw. Beenden des Lauflichtes via PHP :-)</p>

<form action="index.php" method="get">
<input type="hidden" name="Start" value="true">
<input type="submit" value="Starten">
</form>

<form action="index.php" method="get">
<input type="hidden" name="Stop" value="true">
<input type="submit" value="Beenden">
</form>

<?php
    if (isset($_GET["Start"])) {
        echo "Starte Anwendung...<br>";
        $output = shell_exec('sudo /home/pi/Devel/VierLeuchtDioden/laufband/testIt'
                            .' < /home/pi/Devel/nursontest 2>&1');
        echo "<pre>$output</pre>";
        // www-data ALL=NOPASSWD :/home/pi/Devel/VierLeuchtDioden/laufband/testIt
    }
    else if (isset($_GET["Stop"])) {
        echo "Beende Anwendung...<br>";
        $output = shell_exec('sudo killall -SIGINT testIt '
                            .'< /home/pi/Devel/nursontest 2>&1');
        echo "<pre>$output</pre>";
        // www-data ALL=NOPASSWD :/usr/bin/killall
    }
?>

</body>
</html>
