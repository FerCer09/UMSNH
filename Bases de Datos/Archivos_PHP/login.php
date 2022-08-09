<?php
// Include config file
require_once "config.php";

$correo = $contrasena = "";

$correo_err = $contrasena = $contrasena_en = "";

if($_SERVER["REQUEST_METHOD"] == "POST"){

        //Validando correo
        $input_correo = trim($_POST["correo"]);
        if(empty($input_correo)){
                $correo_err = "Porfavor ingrese un correo electronico.";
        }
        else{
                $correo = $input_correo;
        }

        //validando contraseña
        $input_contrasena = trim($_POST["contraseña"]);
        if(empty($input_contrasena)){
                $contrasena_err = "Porfavor ingresa su contraseña.";
        }
        else{
                $contrasena = $input_contrasena;
                $contrasena_en=md5($contrasena);
        }

        if(empty($correo_err) && empty($contrasena_err)){

                $sql = "SELECT * FROM clientes";
                if($result = mysqli_query($link, $sql)){

                        if(mysqli_num_rows($result) > 0){
                                $correo_existe = 0;
                                while($row = mysqli_fetch_array($result)){
                                   if(strcasecmp($row["correo"], $correo) == 0){
                                        $correo_existe = 1;
                                        if($row["contraseña"] == $contrasena_en){
                                            if($row["id"] == 1){
                                                header("location: administrador/productos.php");
                                            }else{
                                                $id = $row["id"];
						header("location: usuario/productos.php?id_cliente=$id");
                                                //header("usuario/productos.php?id_cliente=$id");
                                            }
                                        }else{
                                            $contrasena_err = "La contraseña no es correcta";
                                        }
                                    }
                                }
                                if($correo_existe == 0){
                                    $correo_err = "No existe el cliente";
                                }
                        }else{
                                echo "<p class='lead'><em>No se encontraron resultados.</em></p>";
                        }
                }else{
                        echo "ERROR: No existe la tabla $sql. " . mysqli_error($link);
                }
        }
}
mysqli_close($link);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Iniciar sesion</title>
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
                        <h2>Iniciar sesion</h2>
                    </div>
                    <p>Por favior introduzca su correo electronico y contraseña para iniciar sesion</p>
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">

                        <div class="form-group <?php echo (!empty($correo_err)) ? 'has-error' : ''; ?>">
                            <label>Correo electronico</label>
                            <input type="text" name="correo" class="form-control" value="<?php echo $correo; ?>">
                            <span class="help-block"><?php echo $correo_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($contrasena_err)) ? 'has-error' : ''; ?>">
                            <label>Contraseña</label>
                            <input type="password" name="contraseña" class="form-control" value="<?php echo $contrasena; ?>">
                            <span class="help-block"><?php echo $contrasena_err;?></span>
                        </div>

                        <p>Si no estas registrado,
                            <a href="crear_user.php">da click aqui</a>
                        </p>
                        <input type="submit" class="btn btn-primary" value="Iniciar sesion">
                    </form>
                </div>
            </div>
        </div>
    </div>
</body>
</html>

