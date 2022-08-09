<?php
// Include config file
require_once "config.php";
 
// Define variables and initialize with empty values
$precio = $existencia = $id = "";
$titulo = $descripcion = $caracteristicas = "";

$precio_err = $existencia_err = $id_err = "";
$titulo_err = $descripcion_err = $caracteristicas_err = "";

$img1 = $img2 = $img3 = "";
$img1_err = $img2_err = $img3_err = "";

$foto1 = $foto2 = $foto3 =="";


// Processing form data when form is submitted
if(isset($_POST["id"]) && !empty($_POST["id"])){
    // Get hidden input value
    $id = $_POST["id"];
    $id_cat = $_POST["id_subcat"];

    // Validate titulo
    $input_titulo = trim($_POST["titulo"]);
    if(empty($input_titulo)){
        $titulo_err = "Por favor ingresa el titulo del producto.";
    } else{
        $titulo = $input_titulo;
    }

  // Validate descripcion
    $input_descripcion = trim($_POST["descripcion"]);
    if(empty($input_descripcion)){
        $descripcion_err = "Por favor ingresa la descripcion del producto.";
    } else{
        $descripcion = $input_descripcion;
    }

      // Validate caracteristicas
    $input_caracteristicas = trim($_POST["caracteristicas"]);
    if(empty($input_caracteristicas)){
        $caracteristicas_err = "Por favor ingresa las caracteristicas del producto.";
    } else{
        $caracteristicas = $input_caracteristicas;
    }

    // Validate existencia
    $input_existencia = trim($_POST["existencia"]);
    if(empty($input_existencia)){
        $existencia_err = "Por favor ingresa la existencia del producto.";
    } elseif(!ctype_digit($input_existencia)){
        $existencia_err = "Por favor ingresa un número positivo.";
    } else{
        $existencia = $input_existencia;
    }

     // Validate precio
    $input_precio = trim($_POST["precio"]);
    if(empty($input_precio)){
        $precio_err = "Por favor ingresa el precio del producto.";
    } elseif($input_precio < 0){                        //elseif(!ctype_digit($input_precio)){
        $precio_err = "Por favor ingresa un número positivo.";
    } else{
        $precio = $input_precio;
    }

     //validando imagenes
    $input_img1 = trim($_FILES['archivo1']['name']);
    //$input_img1 = trim($_POST["archivo1"]);
    if( empty($input_img1) ){
        $img1_err = "Ingresa la imagen";
    }else{
        //nombre de la imagen
        $img1 = $input_img1;
        //la imagen
        $foto1 = file_get_contents($_FILES['archivo1']['tmp_name']);
        $sql = "UPDATE imagenes SET imagen =?, foto =? WHERE id_producto = $id AND orden = 1";

        if($stmt = mysqli_prepare($link, $sql)){
             mysqli_stmt_bind_param($stmt, "ss", $param_img, $param_foto);
            // Set parameters
            $param_img = $img1;
            $param_foto = $foto1;
            mysqli_stmt_execute($stmt);
        }
        mysqli_stmt_close($stmt);

    }

    $input_img2 = trim($_FILES['archivo2']['name']);
    //$input_img1 = trim($_POST["archivo1"]);
    if( empty($input_img2) ){
        $img2_err = "Ingresa la imagen";
    }else{
        //nombre de la imagen
        $img2 = $input_img2;
        
        //la imagen
        $foto2 = file_get_contents($_FILES['archivo2']['tmp_name']);
        $sql = "UPDATE imagenes SET imagen=?, foto= ? WHERE id_producto= $id AND orden = 2";

        if($stmt = mysqli_prepare($link, $sql)){
             mysqli_stmt_bind_param($stmt, "ss", $param_img, $param_foto);
            // Set parameters
            $param_img = $img2;
            $param_foto = $foto2;
            mysqli_stmt_execute($stmt);
        }
        mysqli_stmt_close($stmt);
    }

    $input_img3 = trim($_FILES['archivo3']['name']);
    //$input_img1 = trim($_POST["archivo1"]);
    if( empty($input_img3) ){
        $img3_err = "Ingresa la imagen";
    }else{
        //nombre de la imagen
        $img3 = $input_img3;
        
        //la imagen
        $foto3 = file_get_contents($_FILES['archivo3']['tmp_name']);
        $sql = "UPDATE imagenes SET imagen=?, foto= ? WHERE id_producto= $id AND orden = 3";

        if($stmt = mysqli_prepare($link, $sql)){
             mysqli_stmt_bind_param($stmt, "ss", $param_img, $param_foto);
            // Set parameters
            $param_img = $img3;
            $param_foto = $foto3;
            mysqli_stmt_execute($stmt);
        }
        mysqli_stmt_close($stmt);
    }


// Check input errors before inserting in database
    if(empty($titulo_err) && empty($descripcion_err) && empty($caracteristicas_err)&& empty($existencia_err) && empty($precio_err)){
        // Prepare an update statement
        $sql = "UPDATE productos SET titulo=?, descripcion=?, caracteristicas=?, existencia=?, precio=? WHERE id_producto=?";
         
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "sssidi", $param_titulo, $param_descripcion, $param_caracteristicas, $param_existencia, $param_precio, $param_id);
            // Set parameters
            $param_titulo = $titulo;
            $param_descripcion = $descripcion;
            $param_caracteristicas = $caracteristicas;
            $param_existencia = $existencia;
            $param_precio = $precio;
            $param_id = $id;
            
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records updated successfully. Redirect to landing page
            } else{
                echo "Something went wrong. Please try again later.";
            }
        }
         
        // Close statement
        mysqli_stmt_close($stmt);

        $sql = "SELECT * FROM cat_producto WHERE id_categoria = $id_cat AND id_producto = $id";
        
        if($result = mysqli_query($link, $sql)){
            if(mysqli_num_rows($result) == 0){
                //si no existe la relacion categoria-producto, entonces:
                $sql = "INSERT INTO cat_producto VALUES(?,?)";
         
                if($stmt = mysqli_prepare($link, $sql)){
                    // Bind variables to the prepared statement as parameters
                    mysqli_stmt_bind_param($stmt, "ii", $param_cat, $param_id);
                    // Set parameters
                    $param_cat = $id_cat;
                    $param_id = $id;
            
                    // Attempt to execute the prepared statement
                    if(mysqli_stmt_execute($stmt)){
                        // Records updated successfully. Redirect to landing page
                        header("location: productos.php");
                        exit();
                    } else{
                        echo "Something went wrong. Please try again later.";
                    }
                }
            // Close statement
            mysqli_stmt_close($stmt);
            }else{
                header("location: productos.php");
                exit();
            }
        }
        mysqli_stmt_close($stmt);

        //Modificamos la tablas categorias_producto
        

    }
    
    // Close connection
    mysqli_close($link);
} else{
    // Check existence of id parameter before processing further
    if(isset($_GET["id"]) && !empty(trim($_GET["id"]))){
        // Get URL parameter
        $id =  trim($_GET["id"]);
        // Prepare a select statement
        $sql = "SELECT * FROM productos WHERE id_producto = ?";
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "i", $param_id);
            
            // Set parameters
            $param_id = $id;
            
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                $result = mysqli_stmt_get_result($stmt);
    
                if(mysqli_num_rows($result) == 1){
                    /* Fetch result row as an associative array. Since the result set contains only one row, we don't need to use while loop */
                    $row = mysqli_fetch_array($result, MYSQLI_ASSOC);
                    
                    // Retrieve individual field value
                    $titulo = $row["titulo"];
                    $descripcion = $row["descripcion"];
                    $caracteristicas = $row["caracteristicas"];
                    $existencia = $row["existencia"];
                    $precio = $row["precio"];
                } else{
                    // URL doesn't contain valid id. Redirect to error page
                    header("location: productos.php");
                    exit();
                }
                
            } else{
                echo "Oops! Something went wrong. Please try again later.";
            }
        }
        
        // Close statement
        mysqli_stmt_close($stmt);

        $sql = "SELECT * FROM imagenes WHERE id_producto = $id AND orden = 1";
        if($stmt = mysqli_prepare($link, $sql)){
            if(mysqli_stmt_execute($stmt)){
            $result = mysqli_stmt_get_result($stmt);
            if(mysqli_num_rows($result) == 1){
                    $row = mysqli_fetch_array($result,  MYSQLI_ASSOC);
                        // Retrieve individual field value
                    $foto1 = $row["foto"];
                } 
            }
        }
        
        $sql = "SELECT * FROM imagenes WHERE id_producto = $id AND orden = 2";
        if($stmt = mysqli_prepare($link, $sql)){
            if(mysqli_stmt_execute($stmt)){
            $result = mysqli_stmt_get_result($stmt);
            if(mysqli_num_rows($result) == 1){
                    $row = mysqli_fetch_array($result,  MYSQLI_ASSOC);
                        // Retrieve individual field value
                    $foto2 = $row["foto"];
                } 
            }
        }

        $sql = "SELECT * FROM imagenes WHERE id_producto = $id AND orden = 3";
        if($stmt = mysqli_prepare($link, $sql)){
            if(mysqli_stmt_execute($stmt)){
            $result = mysqli_stmt_get_result($stmt);
            if(mysqli_num_rows($result) == 1){
                    $row = mysqli_fetch_array($result,  MYSQLI_ASSOC);
                        // Retrieve individual field value
                    $foto3 = $row["foto"];
                } 
            }
        }
        
        // Close connection
        mysqli_close($link);
    } 
    //checamos la existencia del segundo parametro
    if(isset($_GET["id_cat"]) && !empty(trim($_GET["id_cat"]))){
        $id_cat = trim($_GET["id_cat"]);
    }

}
?>
 
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Update Record</title>
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
                        <h2>Actualizar Registro</h2>
                    </div>
                    <p>Edita los valores y dale clic en aceptar para actualizar el registro.</p>
                    <form action="<?php echo htmlspecialchars(basename($_SERVER['REQUEST_URI'])); ?>" method="post" enctype="multipart/form-data">
                        <div class="form-group <?php echo (!empty($titulo_err)) ? 'has-error' : ''; ?>">
                            <label>Titulo</label>
                            <input type="text" name="titulo" class="form-control" value="<?php echo $titulo; ?>">
                            <span class="help-block"><?php echo $titulo_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($descripcion_err)) ? 'has-error' : ''; ?>">
                            <label>Descripción</label>
                            <textarea name="descripcion" class="form-control"><?php echo $descripcion; ?></textarea>
                            <span class="help-block"><?php echo $descripcion_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($caracteristicas_err)) ? 'has-error' : ''; ?>">
                            <label>Caracteristicas</label>
                            <textarea name="caracteristicas" class="form-control"><?php echo $caracteristicas; ?></textarea>
                            <span class="help-block"><?php echo $caracteristicas_err;?></span>
                        </div>



                        <div class="form-group <?php echo (!empty($existencia_err)) ? 'has-error' : ''; ?>">
                            <label>Existencia</label>
                            <input type="text" name="existencia" class="form-control" value="<?php echo $existencia; ?>">
                            <span class="help-block"><?php echo $existencia_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($precio_err)) ? 'has-error' : ''; ?>">
                            <label>Precio en pesos mexicanos</label>
                            <input type="text" name="precio" class="form-control" value="<?php echo $precio; ?>">
                            <span class="help-block"><?php echo $precio_err;?></span>
                        </div>

                        <div class="form-group">
                            <label>Imagen 1</label>
                            <br>
                            <?php  
                            echo "<img height ='100 px' src = 'data:image/jpg;base64,".base64_encode($foto1)."'>";
                            ?>
                            <input type="file" name="archivo1" accept="image/png, .jpeg, .jpg">
                        </div>

                        <div class="form-group">
                            <label>Imagen 2</label><br>
                            <?php  
                            echo "<img height ='100 px' src = 'data:image/jpg;base64,".base64_encode($foto2)."'>";
                            ?>
                            <input type="file" name="archivo2" accept="image/png, .jpeg, .jpg">
                        </div>

                        <div class="form-group ">
                            <label>Imagen 3</label><br>
                            <?php  
                            echo "<img height ='100 px' src = 'data:image/jpg;base64,".base64_encode($foto3)."'>";
                            ?>
                            <input type="file" name="archivo3" accept="image/png, .jpeg, .jpg">
                            </div>

                        <input type="hidden" name="id" value="<?php echo $id; ?>"/>
                        <input type="hidden" name="id_subcat" value="<?php echo $id_cat; ?>"/>
                        <input type="submit" class="btn btn-primary" value="Aceptar">
                        <a href="productos.php" class="btn btn-default">Cancelar</a>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>

