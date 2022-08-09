<?php
// Include config file
require_once "config.php";
 
// Define variables and initialize with empty values
//$name = $address = $salary = "";

//$name_err = $address_err = $salary_err = "";

//usuarios
$contrasena = $contrasena_err = "";

//DATOS
$nombre = $ape_pa = $ape_ma = $tel = $dom = $n_tarjeta = ""; 
$nombre_err = $ape_pa_err = $ape_ma_err = $tel_err = $dom_err = $n_tarjeta_err = ""; 

//if(isset($_GET["id_cliente"]) && !empty(trim($_GET["id_cliente"]))){
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $id_cliente =$_POST["id_c"];

    // Validate Contraseña
    $input_contrasena = trim($_POST["contraseña"]);
    if(empty($input_contrasena)){
        $contrasena_err = "Por favor ingresa tu contraseña.";
    }else{
        $contrasena = $input_contrasena;
    }

      // Validate Nombre
    $input_nombre = trim($_POST["nombre"]);
    if(empty($input_nombre)){
        $nombre_err = "Por favor ingresa tu nombre";
    } else{
        $nombre = $input_nombre;
    }

    // Validate apellido paterno
    $input_ape_pa = trim($_POST["a_paterno"]);
    if(empty($input_ape_pa)){
        $ape_pa_err = "Por favor ingrese su apellido paterno.";
    } else{
        $ape_pa = $input_ape_pa;
    }

    // Validate apellido materno
    $input_ape_ma = trim($_POST["a_materno"]);
    if(empty($input_ape_ma)){
        $ape_ma_err = "Por favor ingrese su apellido materno.";
    } else{
        $ape_ma = $input_ape_ma;
    }

    //Validando numero de telefono
    $input_tel = trim($_POST["telefono"]);
    if(empty($input_tel)){
        $tel_err = "Por favor ingresa tu numero de telefono.";
    }else if (strlen($input_tel) != 10) {
        $tel_err = "Pon un numero de telefono valido";
    }else if ( !ctype_digit($input_tel) ) {
        $tel_err= "Solo debe contener numeros.";
    } else{
        $tel = $input_tel;
    }

    //Validando domicilio
    $input_dom = trim($_POST["domicilio"]);
    if(empty($input_dom)){
        $dom_err = "Por favor ingrese su domicilio.";
    } else{
        $dom = $input_dom;
    }

    //Validando numero de tarjeta
    $input_n_tar = trim($_POST["n_tarjeta"]);
    if(empty($input_n_tar)){
        $n_tarjeta_err = "Por favor ingresa tu Numero de tarjeta.";
    }else if (strlen($input_n_tar) != 16) {
        $n_tarjeta_err = "Pon un numero de tarjeta valida";
    }else if ( !ctype_digit($input_n_tar) ) {
        $n_tarjeta_err = "Solo debe contener numeros.";
    } else{
        $n_tarjeta = $input_n_tar;
    }

    if(empty($contrasena_err) && empty($nombre_err) && empty($ape_pa_err) && empty($ape_ma_err) && empty($tel_err) && empty($dom_err) && empty($n_tarjeta_err)){   
        // Prepare an insert statement
            $sql = "UPDATE clientes SET contraseña = md5(?) WHERE id= $id_cliente?";
         
            if($stmt = mysqli_prepare($link, $sql)){
                // Bind variables to the prepared statement as parameters
                mysqli_stmt_bind_param($stmt, "s", $param_contrasena);
                // Set parameters
                $param_titulo = $contrasena;
            
                // Attempt to execute the prepared statement
                if(mysqli_stmt_execute($stmt)){
                    // Records updated successfully. Redirect to landing page
                } else{
                    echo "Something went wrong. Please try again later.";
                }
            }
         
            // Close statement
            mysqli_stmt_close($stmt);

            $sql = "UPDATE datos SET nombre=?, a_paterno=?, a_materno=?, telefono=?, domicilio=?, n_tarjeta=aes_encrypt( ? ,'xyz123')  WHERE id_cliente=$id_cliente";
            if($stmt = mysqli_prepare($link, $sql)){
                // Bind variables to the prepared statement as parameters
                mysqli_stmt_bind_param($stmt, "ssssss", $param_nombre, $param_ap_pa, $param_ap_ma, $param_tel, $param_dom, $param_n_tar);
                    // Set parameters
                    $param_nombre = $nombre; 
                    $param_ap_pa = $ape_pa;
                    $param_ap_ma = $ape_ma;
                    $param_tel = $tel;
                    $param_dom = $dom;
                    $param_n_tar = $n_tarjeta;
                // Attempt to execute the prepared statement
                if(mysqli_stmt_execute($stmt)){
                    header("location: productos.php?id_cliente=$id_cliente");
                    exit();
                    // Records updated successfully. Redirect to landing page
                } else{
                    echo "Something went wrong. Please try again later.";
                }
            }
         
            // Close statement
            mysqli_stmt_close($stmt);            
        }
}

// Processing form data when form is submitted
if(isset($_GET["id_cliente"]) && !empty(trim($_GET["id_cliente"]))){
        // Get URL parameter
        $id_cliente =  trim($_GET["id_cliente"]);
        // Prepare a select statement
        $sql = "SELECT * FROM clientes WHERE id = ?";
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "i", $param_id);
            // Set parameters
            $param_id = $id_cliente;
        
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                $result = mysqli_stmt_get_result($stmt);
    
                if(mysqli_num_rows($result) == 1){
                    /* Fetch result row as an associative array. Since the result set contains only one row, we don't need to use while loop */
                    $row = mysqli_fetch_array($result, MYSQLI_ASSOC);
                    
                    // Retrieve individual field value
                    $contrasena = $row["contraseña"]; 
                } else{
                    // URL doesn't contain valid id. Redirect to error page
                    header("location: productos.php?id_cliente=$id_cliente");
                    exit();
                }
                
            } else{
                echo "Oops! Something went wrong. Please try again later.";
            }
        }

        $sql = "SELECT nombre,a_paterno,a_materno,telefono, domicilio, cast(aes_decrypt(n_tarjeta,'xyz123') as char) AS TARJETA FROM datos WHERE id_cliente = ?";
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "i", $param_id);
            // Set parameters
            $param_id = $id_cliente;
        
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                $result = mysqli_stmt_get_result($stmt);
    
                if(mysqli_num_rows($result) == 1){
                    /* Fetch result row as an associative array. Since the result set contains only one row, we don't need to use while loop */
                    $row = mysqli_fetch_array($result, MYSQLI_ASSOC);
                    // Retrieve individual field value
                    $nombre = $row["nombre"]; 
                    $ape_pa = $row["a_paterno"];
                    $ape_ma = $row["a_materno"];
                    $tel = $row ["telefono"];
                    $dom = $row["domicilio"];
                    $n_tarjeta = $row["TARJETA"];

                } else{
                    // URL doesn't contain valid id. Redirect to error page
                    header("location: productos.php?id_cliente=$id_cliente");
                    exit();
                }
                
            } else{
                echo "Oops! Something went wrong. Please try again later.";
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
    <title>Datos Clientes</title>
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
                        <h2>Tus Datos</h2>
                    </div>
                    <p>Edita los valores y dale clic en aceptar para actualizar tus datos.</p>
                    <form action="<?php echo htmlspecialchars(basename($_SERVER['REQUEST_URI'])); ?>" method="post">
                        <div class="form-group <?php echo (!empty($contrasena_err)) ? 'has-error' : ''; ?>">
                            <label>Contraseña (Tu contraseña esta encriptada, edita este campo si quieres cambiar la contraseña)</label>
                            <input type="text" name="contraseña" class="form-control" value="<?php echo $contrasena; ?>">
                            <span class="help-block"><?php echo $contrasena_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($nombre_err)) ? 'has-error' : ''; ?>">
                            <label>Nombre</label>
                            <input type="text" name="nombre" class="form-control" value="<?php echo $nombre; ?>">
                            <span class="help-block"><?php echo $nombre_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($ape_pa_err)) ? 'has-error' : ''; ?>">
                            <label>Apellido Paterno</label>
                            <input type="text" name="a_paterno" class="form-control" value="<?php echo $ape_pa; ?>">
                            <span class="help-block"><?php echo $ape_pa_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($ape_ma_err)) ? 'has-error' : ''; ?>">
                            <label>Apellido Materno</label>
                            <input type="text" name="a_materno" class="form-control" value="<?php echo $ape_ma; ?>">
                            <span class="help-block"><?php echo $ape_ma_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($tel_err)) ? 'has-error' : ''; ?>">
                            <label>Telefono</label>
                            <input type="text" name="telefono" class="form-control" value="<?php echo $tel; ?>">
                            <span class="help-block"><?php echo $tel_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($dom_err)) ? 'has-error' : ''; ?>">
                            <label>Domicilio</label>
                            <input type="text" name="domicilio" class="form-control" value="<?php echo $dom; ?>">
                            <span class="help-block"><?php echo $dom_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($n_tarjeta_err)) ? 'has-error' : ''; ?>">
                            <label>Numero de tarjeta</label>
                            <input type="text" name="n_tarjeta" class="form-control" value="<?php echo $n_tarjeta; ?>">
                            <span class="help-block"><?php echo $n_tarjeta_err;?></span>
                        </div>

                        <input type="hidden" name="id_c" value="<?php echo $id_cliente; ?>"/>
                        <input type="submit" class="btn btn-primary" value="Aceptar">
                        <?php  
                            echo "<a href='productos.php?id_cliente=". $id_cliente ."' class='btn btn-default'>Cancelar</a>"
                        ?>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>

