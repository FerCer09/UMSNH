<?php
// Include config file
require_once "config.php";

if(isset($_GET["id_cliente"]) && !empty(trim($_GET["id_cliente"]))){
        $id_cliente =trim($_GET["id_cliente"]);
}

if(isset($_GET["id"]) && !empty(trim($_GET["id"]))){
        $id_producto =trim($_GET["id"]);
}

// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $id_cliente = $_POST["id_c"];
    $id_producto = $_POST["id_p"];
        
    // Prepare an insert statement
    $sql = "DELETE FROM carrito WHERE id_cliente = $id_cliente and id_producto = $id_producto";        
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            //mysqli_stmt_bind_param($stmt, "s", $param_subcat);
            // Set parameters
            //$param_subcat = $subcat; 
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records created successfully. Redirect to landing page
            //    echo $id_cat;
                //$_GET["id"] = $input_cat;
                header("location: carrito.php?id_cliente=$id_cliente");
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
                            <p>¿Estas seguro de querer quitarlo de tu carrito?</p><br>
                            <p>
                                <input type="submit" value="Si" class="btn btn-danger">
                                <?php
                                echo "<a href='carrito.php?id_cliente=". $id_cliente ."' <class='btn btn-default'>No</a>";
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

