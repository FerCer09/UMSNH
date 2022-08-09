<?php
// Include config file
require_once "config.php";
//obteniedo el id de categoria principal desde la URL
$entrada = "";
$entrada_err = "";

$entrada = trim($_POST["texto"]);

// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){
//    $input_cat = trim($_POST["id_categoria_p"]);
 //   $ip_cat = $input_cat;

    // Validate categoria    
}
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
                        <h2 class="pull-left">Productos</h2>
                        <a href="in_elegir_subcat.php" class="btn btn-success pull-right">Agregar Nuevo Producto</a>
                    </div>
                    <nav>
                        <ul>
                        <a href="categorias.php">Categorias</a>
                        <a href="http://192.168.1.5/login.php">Salir</a>
                        <?php  
                            echo "<a href='pedidos.php'>Pedidos</a>"
                        ?>
                        <?php  
                            echo "<a href='usuarios.php'>Clientes</a>"
                        ?>
                        </ul>
                    </nav>

                    <!--Parte del buscador-->
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                        <div class="form-group <?php echo (!empty($entrada_err)) ? 'has-error' : ''; ?>">
                            <label>Ingrese en el siguiente cuadro lo que gustes buscar:</label>
                            <input type="text" name="texto" class="form-control" value="<?php echo $entrada;?>">
                        </div>
                         <input type="submit" class="btn btn-primary" value="Buscar">
                        <p> </p>
                    </form>
                    <!-- Fin del buscador -->

                    <?php
                    // Include config file
                    require_once "config.php";
                    //SELECT * FROM `productos` AS P,imagenes AS I WHERE I.id_producto = 1 and orden = 1
                    if(empty($entrada)){
                        $sql = "SELECT *, P.descripcion AS DESCR FROM productos AS P,imagenes AS I WHERE I.id_producto = P.id_producto AND orden = 1";
                    }else{
                        $sql = "SELECT *, P.descripcion AS DESCR FROM productos AS P,imagenes AS I WHERE I.id_producto = P.id_producto AND orden = 1 AND (titulo LIKE '%$entrada%' OR P.descripcion LIKE '%$entrada%')";
                    }
                    // Attempt select query execution
                    //$sql = "SELECT * FROM productos";
                    if($result = mysqli_query($link, $sql)){
                        if(mysqli_num_rows($result) > 0){
                            echo "<table class='table table-bordered table-striped'>";
                                echo "<thead>";
                                    echo "<tr>";
                                        echo "<th>#</th>";
                                        echo "<th>Imagen</th>";
                                        echo "<th>Titulo</th>";
                                        echo "<th>Descripción</th>";
                                        echo "<th>Caracteristicas</th>";
                                        echo "<th>Existencia</th>";
                                        echo "<th>Precio(BITCOIN)</th>";
                                    echo "</tr>";
                                echo "</thead>";
                                echo "<tbody>";

                                
                                    while($row = mysqli_fetch_array($result)){
                                        echo "<tr>";
                                            echo "<td>" . $row['id_producto'] . "</td>";
                                            echo "<td> <img height ='100 px' src = 'data:image/jpg;base64,".base64_encode($row['foto'])."'></td>";
                                            //echo "<td> <img src= ". $row['imagen'] ." width=100 height=100 > </td>";
                                            echo "<td>" . $row['titulo'] . "</td>";
                                            echo "<td>" . $row['DESCR'] . "</td>";
                                            echo "<td>" . $row['caracteristicas'] . "</td>";
                                            echo "<td>" . $row['existencia'] . "</td>";
                                            echo "<td>$ " . number_format( $row['precio']*0.0000026,4) . "</td>";
                                            echo "<td>";
                                                echo "<a href='ver.php?id=". $row['id_producto'] ."' title='Ver' data-toggle='tooltip'><span class='glyphicon glyphicon-eye-open'></span></a>";
                                                echo "<a href='elegir_subcat.php?id=". $row['id_producto'] ."' title='Actualizar' data-toggle='tooltip'><span class='glyphicon glyphicon-pencil'></span></a>";
                                                 echo "<a href='delete.php?id_producto=". $row['id_producto'] ."' title='Eliminar' data-toggle='tooltip'><span class='glyphicon glyphicon-trash'></span></a>";
                                                // echo "<a href='insertar.php?id_producto=". $row['id_producto'] ."'title='Comprar' class='btn btn-success pull-right'>Comprar</a>";
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

