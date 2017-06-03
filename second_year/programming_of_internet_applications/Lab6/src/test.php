<?php
  echo '<!DOCTYPE html><html><head><meta charset="utf-8" /></head><body><h1>Result</h1>';
  $beginning = microtime();
  for ($i = 1; $i <= 9; $i++) {
      $xs[$i] = $_GET['x'.$i];
  }
  $y = $_GET['y'];
  $r = $_GET['radius'];

  echo "<table style='border: 2px solid black; border-collapse: collapse; padding : 5px; margin-left: 20px;'>";
  echo "<tr><td style='border: 2px solid black; border-collapse: collapse; padding : 5px; margin-left: 20px;'>x</td><td
  style='border: 2px solid black; border-collapse: collapse; padding : 5px; margin-left: 20px;'>y</td>
  <td style='border: 2px solid black; border-collapse: collapse; padding : 5px; margin-left: 20px;'>in area</td></tr>";
  for ($i = 1; $i <= 9; $i++) {
      if($xs[$i]!=''){
          echo "<tr>";
          echo '<td style="border: 2px solid black; border-collapse: collapse; padding : 5px; margin-left: 20px;">';
          echo $xs[$i];
          echo'</td>';
          echo '<td style="border: 2px solid black; border-collapse: collapse; padding : 5px; margin-left: 20px;">';
          echo $y;
          echo'</td>';
          echo '<td style="border: 2px solid black; border-collapse: collapse; padding : 5px; margin-left: 20px;">';

          if(($xs[$i] < 0 && $y > 0 && sqrt($xs[$i]*$xs[$i] +$y*$y) < $r) || ($xs[$i] > 0 && $y < 0 && $xs[$i] < $r && $y > $r/2)
          || ($xs[$i] > 0 && $y > 0 && $xs[$i]+$y<$r/2)){
            echo "true";
          } else {
            echo "false";
          }
          echo'</td>';
          echo"</tr>";
      }

  }
  echo "</table>";
  $ending = microtime();
  echo "<p>Executed at ".date("H:i:s", time())." in ".($ending - $beginning)." sec.</p>";
  echo '</body></html>';
?>
