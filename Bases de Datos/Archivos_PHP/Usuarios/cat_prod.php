<?php
// Include config file
require_once "config.php";
//obteniedo el id de categoria principal desde la URL
$entrada = "";
$entrada_err = "";

if(isset($_GET["id"]) && !empty(trim($_GET["id"]))){
    	$id_subcat =trim($_GET["id"]);
}

if(isset($_GET["id_cat"]) && !empty(trim($_GET["id_cat"]))){
    	$id_cat =trim($_GET["id_cat"]);
}

if(isset($_GET["id_cliente"]) && !empty(trim($_GET["id_cliente"]))){
        $id_cliente =trim($_GET["id_cliente"]);
}

if($_SERVER["REQUEST_METHOD"] == "POST"){
//    $input_cat = trim($_POST["id_categoria_p"]);
 //   $ip_cat = $input_cat;
	$id_subcat = $_POST["id"];
	$id_cat = $_POST["id_cat"];
	$entrada = trim($_POST["texto"]);
    $id_cliente = $_POST["id_c"];
        // Validate categoria    
}

/*
COnsulta para ver a todos los productos de la categoria consolas
SELECT p.titulo, c.categoria, c.id FROM cat_producto AS cp,categorias AS c,productos AS p WHERE  cp.id_categoria = c.id and cp.id_producto = p.id_producto and c.id =11;
*/

// Processing form data when form is submitted
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Productos de Categorias</title>
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
                        <h2 class="pull-left">Productos de la categoria </h2>
                    </div>
                    <nav>
                        <ul>
                        
                        </ul>
                    </nav>

                    <!--Parte del buscador-->
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                        <div class="form-group <?php echo (!empty($entrada_err)) ? 'has-error' : ''; ?>">
                            <label>Ingrese en el siguiente cuadro lo que gustes buscar:</label>
                            <input type="text" name="texto" class="form-control" value="<?php echo $entrada;?>">
                        </div>

                        <input type="hidden" name="id_c" value="<?php echo $id_cliente; ?>"/>
                        <input type="hidden" name="id" value="<?php echo $id_subcat; ?>"/>
                        <input type="hidden" name="id_cat" value="<?php echo $id_cat; ?>"/>
                         <input type="submit" class="btn btn-primary" value="Buscar">
                        <p> </p>
                    </form>
                    <!-- Fin del buscador -->

                    <?php
                    // Include config file
                    require_once "config.php";
                    if(empty($entrada)){
                    	$sql = "SELECT p.id_producto, p.titulo,p.precio, c.categoria, c.id FROM cat_producto AS cp,categorias AS c,productos AS p WHERE  cp.id_categoria = c.id and cp.id_producto = p.id_producto and c.id = $id_subcat";
                    }else{
                        $sql = "SELECT p.id_producto, p.titulo,p.precio, c.categoria, c.id FROM cat_producto AS cp,categorias AS c,productos AS p WHERE  cp.id_categoria = c.id and cp.id_producto = p.id_producto and c.id = $id_subcat and (p.titulo LIKE '%$entrada%' OR descripcion LIKE '%$entrada%')";
                    }
                    // Attempt select query execution
                    //$sql = "SELECT * FROM productos";
                    if($result = mysqli_query($link, $sql)){
                        if(mysqli_num_rows($result) > 0){
                            echo "<table class='table table-bordered table-striped'>";
                                echo "<thead>";
                                    echo "<tr>";
                                        echo "<th>Titulo</th>";
                                        echo "<th>Precio (Bitcoins)</th>";
                                    echo "</tr>";
                                echo "</thead>";
                                echo "<tbody>";
                                    while($row = mysqli_fetch_array($result)){
                                        echo "<tr>";
                                            echo "<td>" . $row['titulo'] . "</td>";
                                            echo "<td>$ " . number_format( $row['precio']*0.0000026,4) . "</td>";
                                            echo "<td>";
                                                echo "<a href='ver.php?id_cliente=". $id_cliente ."&id=". $row['id_producto'] ."' title='Ver' data-toggle='tooltip'><span class='glyphicon glyphicon-eye-open'></span></a>";
                                                //echo "<a href='elegir_subcat.php?id=". $row['id_producto'] ."' title='Actualizar' data-toggle='tooltip'><span class='glyphicon glyphicon-pencil'></span></a>";
                                                //echo "<a href='delete.php?id_producto=". $row['id_producto'] ."' title='Eliminar' data-toggle='tooltip'><span class='glyphicon glyphicon-trash'></span></a>";
                                                echo "<a href='user_pro.php?id_cliente=". $id_cliente ."&id_producto=". $row['id_producto'] ."'title='add carrito' class='btn btn-success pull-right'>Añadir al Carrito</a>";
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
                    echo "<a href='subcategorias.php?id_cliente=". $id_cliente ."&id=". $id_cat ."'title='sub_categorias' class='btn btn-success pull-right'>Salir</a>";
                     
                    // Close connection
                    mysqli_close($link);
                    ?>
                </div>
            </div>
        </div>
    </div>
</body>
</html>

