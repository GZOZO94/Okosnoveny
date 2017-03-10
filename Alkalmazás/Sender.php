<?php
	$answer="Failed";
	/*a herokuhoz való kapcsolódás, amin postgresql adatbázis található*/
	$con = pg_connect("host=ec2-54-247-92-185.eu-west-1.compute.amazonaws.com port=5432 dbname=d5gj5g31fed3l9
	password=fbb2bb17bd2bbfe53e6bc06b32409401a59c520763e0f8d146a6cec193b2dea7");
			if (!$con) {
				echo "Error with connecting.\n";
				exit;
			}
	$temp=$_GET['temp'];
	$hum=$_GET['hum'];
	if($temp!=NULL && $hum!=NULL){
		$query=sprintf("insert into datas(temp,hum) values(%f,%f)",$temp,$hum);
		pg_query($con,$query);
		$answer="Succeed";
	}
	echo $answer;
?>