<?php
// Process delete operation after confirmation
$id = trim($_POST["id"]);
if(isset($_POST["id_categoria"]) && !empty($_POST["id_categoria"])){
    // Include config file
    require_once "config.php";
    // Prepare a delete statement
    $sql = "DELETE FROM categorias WHERE id = ?";
    //echo $_POST["id_producto"];
    $sub_cat = trim($_POST["id_categoria"]);
    if($stmt = mysqli_prepare($link, $sql)){
        // Bind variables to the prepared statement as parameters
        mysqli_stmt_bind_param($stmt, "i", $param_id);
        
        // Set parameters
        $param_id = $sub_cat;
        
        // Attempt to execute the prepared statement
        if(mysqli_stmt_execute($stmt)){
            // Records deleted successfully. Redirect to landing page
            header("location: subcategorias.php?id=$id");
            //exit();
        } else{
            echo "Oops! Something went wrong. Please try again later.";
        }
    }
     
    // Close statement
    mysqli_stmt_close($stmt);
    
    // Close connection
    mysqli_close($link);
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
                        <h1>Eliminar Categoria Secundaria</h1>
                    </div>
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                        <div class="alert alert-danger fade in">
                            <input type="hidden" name="id_categoria" value="<?php echo $_GET["id_subcat"]; ?>"/>
                            <input type="hidden" name="id" value="<?php echo $_GET["id_cat"]; ?>"/>
                            <p>¿Estas seguro de eliminar este registro?</p><br>
                            <p>
                                <input type="submit" value="Si" class="btn btn-danger">
                                <?php
                                echo "<a href='subcategorias.php?id=". $_GET["id_cat"] ."'title='sub_categorias' class='btn btn-default'>No</a>";
                                ?>
                             <!--   <a href="subcategorias?id=$_GET[id_cat].php" class="btn btn-default">No</a>  -->
                            </p>
                        </div>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>

