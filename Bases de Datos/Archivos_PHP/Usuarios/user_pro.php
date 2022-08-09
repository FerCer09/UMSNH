<?php
// Include config file
require_once "config.php";

if(isset($_GET["id_cliente"]) && !empty(trim($_GET["id_cliente"]))){
        $id_cliente =trim($_GET["id_cliente"]);
}

if(isset($_GET["id_producto"]) && !empty(trim($_GET["id_producto"]))){
        $id_producto =trim($_GET["id_producto"]);
}

// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $id_cliente = $_POST["id_c"];
    $id_producto = $_POST["id_p"];

    $sql = "DELETE FROM carrito WHERE id_cliente = $id_cliente AND NOW() > DATE_ADD(instante,INTERVAL 30 MINUTE)";
    if($stmt = mysqli_prepare($link, $sql)){
        // Bind variables to the prepared statement as paramete
        // Attempt to execute the prepared statement
        mysqli_stmt_execute($stmt);
    }
    mysqli_stmt_close($stmt);

    $sql = "UPDATE carrito SET instante = NOW() WHERE id_cliente = $id_cliente";
    if($stmt = mysqli_prepare($link, $sql)){
        mysqli_stmt_execute($stmt);
    }
    // Close statement
    mysqli_stmt_close($stmt);


    // Prepare an insert statement
    $sql = "INSERT INTO carrito(id_cliente,id_producto) VALUES ($id_cliente,$id_producto)";        
        if($stmt = mysqli_prepare($link, $sql)){
            if(mysqli_stmt_execute($stmt)){
                // Records created successfully. Redirect to landing page
            //    echo $id_cat;
                //$_GET["id"] = $input_cat;
                header("location: productos.php?id_cliente=$id_cliente");
                //header("location: subcategoris.php");
                exit();
            } else{
                echo "Something went wrong. Please try again later.";
            }
        }
        // Close statement
        mysqli_stmt_close($stmt);
    }

    // Close connection
    mysqli_close($link);        
?>
 
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Agregar Carrito</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css">
    <style type="text/css">
        .wrapper{
            width: 500px;
            margin: 0 auto;
        }
    </style>
</head>
<body>
    <div class="wrapper">
        <div class="container-fluid">
            <div class="row">
                <div class="col-md-12">
                    <div class="page-header">
                        <h2>Añadir al carrito</h2>
                    </div>
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                        <div class="alert alert-danger fade in">
                            <input type="hidden" name="id_c" value="<?php echo $id_cliente; ?>"/>
                            <input type="hidden" name="id_p" value="<?php echo $id_producto; ?>"/>
                            <p>¿Estas seguro de querer agregarlo a tu carrito?</p><br>
                            <p>
                                <input type="submit" value="Si" class="btn btn-danger">
                                <?php
                                echo "<a href='productos.php?id_cliente=". $id_cliente ."' <class='btn btn-default'>No</a>";
                                ?>
                            </p>
                        </div>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>

