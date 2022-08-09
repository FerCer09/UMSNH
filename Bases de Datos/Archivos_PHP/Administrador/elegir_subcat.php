<?php
// Include config file
require_once "config.php";
//obteniedo el id de categoria principal desde la URL
// Processing form data when form is submitted
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Productos de myamazon</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.js"></script>
    <style type="text/css">
        .wrapper{
            width: 650px;
            margin: 0 auto;
        }
        .page-header h2{
            margin-top: 0;
        }
        table tr td:last-child a{
            margin-right: 15px;
        }
    </style>
    <script type="text/javascript">
        $(document).ready(function(){
            $('[data-toggle="tooltip"]').tooltip();
        });
    </script>
</head>
<body>
    <div class="wrapper">
        <div class="container-fluid">
            <div class="row">
                <div class="col-md-12">
                    <div class="page-header clearfix">
                        <h2 class="pull-left">Seleccionar Subcategoria</h2>
                    </div>

                    <?php 
                    $id_producto = $_GET["id"];
                    // Include config file
                    require_once "config.php";
                    
                    // Attempt select query execution
                    $sql = "SELECT * FROM categorias WHERE id_categoria IS NOT NULL";
                    if($result = mysqli_query($link, $sql)){
                        if(mysqli_num_rows($result) > 0){
                            echo "<table class='table table-bordered table-striped'>";
                                echo "<thead>";
                                    echo "<tr>";
                                        echo "<th>Subcategoria</th>";
                                    echo "</tr>";
                                echo "</thead>";
                                echo "<tbody>";
                                    while($row = mysqli_fetch_array($result)){
                                        echo "<tr>";
                                            echo "<td>" . $row['categoria'] . "</td>";
                                            echo "<td>";
                                                //echo "<a href='ver.php?id=". $row['id_producto'] ."' title='Ver' data-toggle='tooltip'><span class='glyphicon glyphicon-eye-open'></span></a>";
                                                //echo "<a href='update.php?id=". $row['id_producto'] ."&id_cat=". $row['id_producto'] ."' title='sel' data-toggle='tooltip'><span class='glyphicon glyphicon-pencil'></span></a>";
     //                                            echo "<a href='delete.php?id_producto=". $row['id_producto'] ."' title='Eliminar' data-toggle='tooltip'><span class='glyphicon glyphicon-trash'></span></a>";
                                                echo "<a href='update.php?id=". $id_producto ."&id_cat=". $row['id'] ."'title='Selec' class='btn btn-success pull-right'>Seleccionar</a>";
                                            echo "</td>";
                                        echo "</tr>";
                                    }
                                echo "</tbody>";
                            echo "</table>";
                            // Free result set
                            mysqli_free_result($result);
                        } else{
                            echo "<p class='lead'><em>No records were found.</em></p>";
                        }
                    } else{
                        echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
                    }
                    // Close connection
                    mysqli_close($link);
                    ?>
                </div>
            </div>
        </div>
    </div>
</body>
</html>

