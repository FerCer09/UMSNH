<?php
// Include config file
require_once "config.php";
if(isset($_GET["id_cliente"]) && !empty(trim($_GET["id_cliente"]))){
        $id_cliente =trim($_GET["id_cliente"]);
}

if($_SERVER["REQUEST_METHOD"] == "POST"){
    $id_cliente = $_POST["id_c"];
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Categorias de myamazon</title>
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
                        <h2 class="pull-left">Categorias Principales</h2>
<!--                    <a href="crear_cat.php" class="btn btn-success pull-right">Agregar Nueva Categoria</a>  -->
                    </div>
                    <nav>
                        <ul>
    <!--                    <a href="http://192.168.0.5/administrador/productos.php">    Salir</a>          -->
                            <?php  
                            echo "<a href='productos.php?id_cliente=". $id_cliente ."'>Salir</a>"
                            ?>
                        </ul>
                    </nav>
                    <?php
                    // Include config file
                    require_once "config.php";
                    // Attempt select query execution
                    $sql = "SELECT id,categoria FROM categorias WHERE id_categoria IS NULL";
                    if($result = mysqli_query($link, $sql)){
                        if(mysqli_num_rows($result) > 0){
                            echo "<table class='table table-bordered table-striped'>";
                                echo "<thead>";
                                    echo "<tr>";
                                        echo "<th>Nombre de Categoria</th>";
                                    echo "</tr>";
                                echo "</thead>";
                                echo "<tbody>";
                                    while($row = mysqli_fetch_array($result)){
                                        echo "<tr>";
                                            echo "<td>" . $row['categoria'] . "</td>";
                                            echo "<td>";
                                //                echo "<a href='ver.php?id=". $row['id_producto'] ."' title='Ver' data-toggle='tooltip'><span class='glyphicon glyphicon-eye-open'></span></a>";
                                //                echo "<a href='update.php?id=". $row['id_producto'] ."' title='Actualizar' data-toggle='tooltip'><span class='glyphicon glyphicon-pencil'></span></a>";
                                //                 echo "<a href='delete.php?id_producto=". $row['id_producto'] ."' title='Eliminar' data-toggle='tooltip'><span class='glyphicon glyphicon-trash'></span></a>";
                                               echo "<a href='subcategorias.php?id_cliente=". $id_cliente ."&id=". $row['id'] ."'title='Subcategorias' class='btn btn-success pull-right'>Subcategorias</a>";
                                //               echo "<a href='elim_cat.php?id=". $row['id'] ."'title='Eliminar_Categorias' class='btn btn-success pull-right'>Eliminar</a>";
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
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                        <input type="hidden" name="id_c" value="<?php echo $id_cliente; ?>"/>
                    </form>
                </div>
            </div>
        </div>
    </div>
</body>
</html>

