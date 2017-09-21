<html>
    <head>
        <title>House</title>
        <meta charset="UTF-8">
        <link rel="stylesheet" href="main.css" type="text/css">
    </head>
    <body>
        <audio autoplay>
            <source src="Horse.mp3" type="audio/mpeg">
        </audio>
        <audio autoplay>
            <source src="petit_poney.mp3" type="audio/mpeg">
        </audio>
        
        <form action="House.php" method="get">
            <input type="submit" value="Uppdatera" id="reload"/>
        </form>
        <form action="House_Med.php" method="get">
           <input type="submit" value="Medelvärdet" id="Med_vard"/> 
        </form>
        
        <input type="submit" value="NO!" onclick="NO()"/>
        <script type="text/javascript">
            function NO() {
                var x = document.getElementById('Gif');
                
                if (x.style.display === 'block') {
                    x.style.display = 'none';
                }else{
                    x.style.display = 'block';
                }
            }
        </script>
        <?php
            $myfile = fopen("Med_Dag.txt", "r") or die("Unable to open file!");
        ?>
        <div id="Gif"></div>
        <div id="house">
            <div id="half">
                <div id="liv_room">
                    <h3>Vardagsrum</h3>
                    <?php
                        $Output;
                        $x = 0;
                        print"C°: ";
                        while($x < 10){
                            $Output = fgetc($myfile);    
                                
                          
                                if($x == 2){
                                    print"<br>";
                                }
                                else if($x == 3){
                                    print"Dag: ";
                                }
                                echo($Output); 
                            
                            $x++;
                        }
                    ?>
                </div>
                <div id="kitchen">
                    <h3>Kök</h3>
                    <?php
                        $y = 10;
                    
                        print"C°: ";
                        while($y < 21){
                            $Output = fgetc($myfile);    
                                
                            if($y == 13){
                                print"<br>";
                            }
                            else if($y == 14){
                                print"Dag: ";
                            }
                            echo($Output);
                            
                            $y++;
                        }
                    ?>
                </div>    
            </div>
            <div id="half">
                <div id="bathroom">
                    <h3>Badrum</h3>
                    <?php
                        $z = 19;                
                        
                        print"C°: ";
                        while($z < 30){
                            $Output = fgetc($myfile);    
                                
                            if($z == 22){
                                print"<br>";
                            }
                            else if($z == 23){
                                print"Dag: ";
                            }
                            echo($Output);
                            
                            $z++;
                        }
                    ?>
                </div>
                <div id="bedroom">
                    <h3>Sovrum</h3>
                    <?php
                        $w = 28;
                    
                        print"C°: ";
                        while($w < 39){
                            $Output = fgetc($myfile);    
                            
                            if($w == 31){
                                print"<br>";
                            }
                            else if($w == 32){
                                print"Dag: ";
                            }
                            echo($Output);

                            $w++;
                        }
                        fclose($myfile);
                    ?>
                </div>
            </div>
        </div>
    </body>
</html>