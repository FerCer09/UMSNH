<?/*php  
SELECT c.correo, p.titulo,DATE_FORMAT(cp.instante,'%h:%i %p of %M %e, %Y') AS fecha FROM carrito AS cp,clientes AS c, productos as p WHERE cp.id_cliente = c.id AND cp.id_producto = p.id_producto

//El pedido del cliente 2
SELECT c.correo, p.titulo,pc.precio,DATE_FORMAT(pc.fecha,'%h:%i %p of %M %e, %Y') AS FECHA FROM pedidos AS pc,clientes AS c, productos as p WHERE pc.id_cliente = c.id AND pc.id_producto = p.id_producto and c.id = 2
*/?>

<?php
// Include config file
require_once "config.php";
//obteniedo el id de categoria principal desde la URL



?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Pedidos</title>
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
                        <h2 class="pull-left">Todos los Pedidos</h2>
                    </div>
                    <nav>
                        <ul>
                        
                        </ul>
                    </nav>

                    <?php
                    // Include config file
                    require_once "config.php";
                    $sql = "SELECT c.correo, p.id_producto AS ID, p.titulo,pc.precio AS PRECIO,DATE_FORMAT(pc.fecha,'%h:%i %p of %M %e, %Y') AS FECHA, cantidad FROM pedidos AS pc,clientes AS c, productos as p WHERE pc.id_cliente = c.id AND pc.id_producto = p.id_producto ORDER BY FECHA";

                   // $sql = "SELECT p.id_producto, p.titulo,p.precio, c.categoria, c.id FROM cat_producto AS cp,categorias AS c,productos AS p WHERE  cp.id_categoria = c.id and cp.id_producto = p.id_producto and c.id = $id_subcat and p.titulo LIKE '%$entrada%'";
                    
                    // Attempt select query execution
                    //$sql = "SELECT * FROM productos";
                    if($result = mysqli_query($link, $sql)){
                        if(mysqli_num_rows($result) > 0){
                            echo "<table class='table table-bordered table-striped'>";
                                echo "<thead>";
                                    echo "<tr>";
                                        echo "<th>Usuario</th>";
                                        echo "<th>Titulo</th>";
                                        echo "<th>Precio (Bitcoins)</th>";
                                        echo "<th>Cantidad</th>";
                                    	echo "<th>Fecha de compra </th>";
                                    echo "</tr>";
                                echo "</thead>";
                                echo "<tbody>";
                                    while($row = mysqli_fetch_array($result)){
                                        echo "<tr>";
                                            echo "<td> " . $row['correo'] . "</td>";
                                            echo "<td>" . $row['titulo'] . "</td>";
                                            echo "<td>$ " . number_format( $row['PRECIO']*0.0000026,4) . "</td>";
                                            echo "<td>" . $row['cantidad'] . "</td>";
                                            echo "<td>" . $row['FECHA'] . "</td>";
                                            echo "<td>";

                                                echo "<a href='ver.php?id_cliente=". $id_cliente ."&id=". $row['ID'] ."' title='Ver' data-toggle='tooltip'><span class='glyphicon glyphicon-eye-open'></span></a>";
                                                //echo "<a href='elegir_subcat.php?id=". $row['id_producto'] ."' title='Actualizar' data-toggle='tooltip'><span class='glyphicon glyphicon-pencil'></span></a>";
                                                //echo "<a href='delete.php?id_producto=". $row['id_producto'] ."' title='Eliminar' data-toggle='tooltip'><span class='glyphicon glyphicon-trash'></span></a>";
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

                    <!--Parte del buscador-->
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                        <input type="hidden" name="id_c" value="<?php echo $id_cliente; ?>"/>
                        <?php  
                            echo "<a href='productos.php' class='btn btn-success pull-right'>Salir</a>"
                        ?>
                        <p> </p>
                    </form>
                    <!-- Fin del buscador -->
                </div>
            </div>
        </div>
    </div>
</body>
</html>

