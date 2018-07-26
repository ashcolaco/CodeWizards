package org.ash.trafficemergency;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.os.Environment;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import org.apache.commons.net.ftp.FTP;
import org.apache.commons.net.ftp.FTPClient;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.net.SocketException;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (ContextCompat.checkSelfPermission(this,
                Manifest.permission.ACCESS_FINE_LOCATION)
                != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION,Manifest.permission.WRITE_EXTERNAL_STORAGE},2);
        }


        final TextView textView = findViewById(R.id.LocationView);
        ToggleButton toggle = (ToggleButton) findViewById(R.id.toggleButton);
        final LocationManager locationManager = (LocationManager) this.getSystemService(Context.LOCATION_SERVICE);
        toggle.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    final String Vehicle_Number = "veh_data.txt";

                    // Define a listener that responds to location updates
                    LocationListener locationListener = new LocationListener() {
                        public void onLocationChanged(Location location) {
                            double latitude = location.getLatitude();
                            double longitude = location.getLongitude();
                            textView.setText(latitude + ","+longitude);
                            try {
                                File root = new File(Environment.getExternalStorageDirectory(), "Notes");
                                if (!root.exists()) {
                                    root.mkdirs();
                                }
                                File emergency_vehicle = new File(root, Vehicle_Number);
                                FileWriter writer = new FileWriter(emergency_vehicle);
                                writer.append(String.valueOf(latitude));
                                writer.flush();
                                writer.close();
                                Toast.makeText(getApplicationContext(),"Saved",Toast.LENGTH_LONG).show();
                                FTPClient mFTP = new FTPClient();
                                // Connect to FTP Server
                                mFTP.connect("192.168.43.31:2121");
                                //mFTP.login("ADMIN", "aDmIn");
                                mFTP.setFileType(FTP.BINARY_FILE_TYPE);
                                mFTP.enterLocalPassiveMode();

                                // Prepare file to be uploaded to FTP Server
                                File file = new File(getFileStreamPath("veh_data.txt")+ "");
                                FileInputStream ifile = new FileInputStream(file);

                                // Upload file to FTP Server
                                mFTP.storeFile("filetotranfer",ifile);
                                mFTP.disconnect();
                            } catch (SocketException e) {
                                // TODO Auto-generated catch block
                                e.printStackTrace();
                            } catch (IOException e) {
                                // TODO Auto-generated catch block
                                e.printStackTrace();
                            }
                        }


                        public void onStatusChanged(String provider, int status, Bundle extras) {}

                        public void onProviderEnabled(String provider) {}

                        public void onProviderDisabled(String provider) {}
                    };
                    locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 0, 0, locationListener);

                } else {
                    // The toggle is disabled

                }
            }
        });





    }
}
