<?php
// Include config file
require_once "config.php";
 
$cat = "";
$cat_err = "";

// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){

    // Validate cat correo
    $input_cat = trim($_POST["categoria"]);
    if(empty($input_cat)){
        $cat_err = "Por favor el nombre de la categoria";
    } else{
        $cat = $input_cat;
    }

    // Check input errors before inserting in database
    if(empty($cat_err)){   
        // Prepare an insert statement
        $sql = "INSERT INTO categorias(categoria) VALUES (?)";
            
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "s", $param_cat);
            // Set parameters
            $param_cat = $cat; 

            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records created successfully. Redirect to landing page
                header("location: categorias.php");
                exit();
            } else{
                echo "Something went wrong. Please try again later.";
            }
        }
        // Close statement
        mysqli_stmt_close($stmt);
    }
    
}
    // Close connection
    mysqli_close($link);
?>
 
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Categoria</title>
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
                        <h2>Crear Categoria</h2>
                    </div>
                    <p>Introduce el nombre de la categoria y da clic en Aceptar para agregarla.</p>
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                        <div class="form-group <?php echo (!empty($cat_err)) ? 'has-error' : ''; ?>">
                            <label>Nombre de la Categoria</label>
                            <input type="text" name="categoria" class="form-control" value="<?php echo $cat; ?>">
                            <span class="help-block"><?php echo $cat_err;?></span>
                        </div>

                        <input type="submit" class="btn btn-primary" value="Aceptar">
                        <a href="categorias.php" class="btn btn-default">Cancelar</a>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>
