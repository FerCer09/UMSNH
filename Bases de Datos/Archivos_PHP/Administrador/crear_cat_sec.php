<?php
// Include config file
require_once "config.php";
//obteniedo el id de categoria principal desde la URL
$subcat = "";
$subcat_err = "";
$id_cat = $_GET["id"];
$input_cat = trim($_POST[id_categoria_p]);
echo $id_cat;
echo $input_cat;
// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){
//    $input_cat = trim($_POST["id_categoria_p"]);
 //   $ip_cat = $input_cat;

    // Validate categoria
    $input_subcat = trim($_POST["categoria"]);
    if(empty($input_subcat)){
        $subcat_err = "Por favor el nombre de la subcategoria";
    } else{
        $subcat = $input_subcat;
    }

    // Check input errors before inserting in database
    if(empty($subcat_err) ){   
        //obteniendo el id del ultimo usuario agregado
        
        // Prepare an insert statement
        $sql = "INSERT INTO categorias(id_categoria,categoria) VALUES ($input_cat,?)";
            
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "s", $param_subcat);
            // Set parameters
            $param_subcat = $subcat; 

            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records created successfully. Redirect to landing page
            //    echo $id_cat;
                //$_GET["id"] = $input_cat;
                header("location: subcategorias.php?id=$input_cat");
                //header("location: subcategorias.php");
              //  exit();
            } else{
                echo "Something went wrong. Please try again later.";
            }
        }
        // Close statement
        mysqli_stmt_close($stmt);
    }
    else{
        header("crear_cat_sec.php?id=$input_cat");
    }
    
}
    
    // Close connection
    mysqli_close($link);
?>
 
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Subcategoria</title>
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
                        <h2>Crear Categoria Secundaria</h2>
                    </div>
                    <p>Introduce el nombre de la subcategoria y da clic en Aceptar para agregarla.</p>
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                        <div class="form-group <?php echo (!empty($subcat_err)) ? 'has-error' : ''; ?>">
                            <label>ID de Categoria principal</label>
                            <input type="text" name="id_categoria_p" class="form-control" value="<?php echo $_GET['id'];?>">
                        </div>

                        <div class="form-group <?php echo (!empty($subcat_err)) ? 'has-error' : ''; ?>">
                            <label>Nombre de la Categoria Secundaria</label>
                            <input type="text" name="categoria" class="form-control" value="<?php echo $subcat; ?>">
                            <span class="help-block"><?php echo $subcat_err;?></span>
                        </div>

                        <input type="submit" class="btn btn-primary" value="Aceptar">
                        <?php
                        echo "<a href='subcategorias.php?id=". $id_cat ."'title='sub_categorias' class='btn btn-success pull-right'>Cancelar</a>";
                        ?>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>
