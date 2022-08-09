<?php
// Process delete operation after confirmation
if(isset($_POST["id_producto"]) && !empty($_POST["id_producto"])){
    // Include config file
    require_once "config.php";
    
    // Prepare a delete statement
    $sql = "DELETE FROM productos WHERE id_producto = {$_POST['id_producto']}";
    //echo $_POST["id_producto"];
    
    if($stmt = mysqli_prepare($link, $sql)){
        // Bind variables to the prepared statement as parameters
        mysqli_stmt_bind_param($stmt, "i", $param_id);
        
        // Set parameters
        $param_id = trim($_POST["id_producto"]);
        
        // Attempt to execute the prepared statement
        if(mysqli_stmt_execute($stmt)){
            // Records deleted successfully. Redirect to landing page
            header("location: productos.php");
            exit();
        } else{
            echo "Oops! Something went wrong. Please try again later.";
        }
    }
     
    // Close statement
    mysqli_stmt_close($stmt);
    
    // Close connection
    mysqli_close($link);
} else{
//    echo "lo que no se cumplio 'id_producto'";
    // Check existence of id parameter
    if(empty(trim($_GET["id_producto"]))){
        // URL doesn't contain id parameter. Redirect to error page
	echo "NO se elimino {$_GET['id_producto']}";
	echo "Ocurrio un error";
//        header("location: error.php");
	header("location: productos.php");
        exit();
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Eliminación</title>
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
                        <h1>Eliminar Registro</h1>
                    </div>
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                        <div class="alert alert-danger fade in">
                            <input type="hidden" name="id_producto" value="<?php echo trim($_GET["id_producto"]); ?>"/>
                            <p>¿Estas seguro de eliminar este registro?</p><br>
                            <p>
                                <input type="submit" value="Si" class="btn btn-danger">
                                <a href="productos.php" class="btn btn-default">No</a>
                            </p>
                        </div>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>

