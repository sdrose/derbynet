<?php

if (isset($_POST['name'])) {
  $name = $_POST['name'];
  $password = $_POST['password'];
  // Don't want the password parroted back in the response.
  $_POST['password'] = '...';
 } else {
  $name = '';
  $password = '';
}

start_response();

$role = $roles[$name];

if ($role) {
  if ($password == $role['password']) {
    $_SESSION['permissions'] = $role['permissions'];
    if (empty($name) && isset($_SESSION['setting_up'])) {
      unset($_SESSION['setting_up']);
    }      
    // Some clients are scripts running from RPi's or similar devices that may
    // not have an accurate clock.  The timecheck element allows the device to
    // be set reasonably close to the date.
    echo "\n<timecheck>".date(DATE_ISO8601)."</timecheck>\n";
    if ($password) {
      $_SESSION['role'] = $name;
	  echo '<success>'.$_SESSION['role'].'</success>'."\n";
	} else {
      // Despite the unset, it appears $_SESSION['role'] will appear
      // as an empty string in subsequent accesses.
      unset($_SESSION['role']);
	  echo '<success/>'."\n";
	}
  } else {
    echo '<failure>Incorrect password</failure>'."\n";
  }
} else {
  echo '<failure role="'.$name.'">No such role: '.$name.'</failure>'."\n";
}

end_response();
?>